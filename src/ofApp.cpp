/*
 
 notes:
 - maybe in the futre, for optimization purposes, i can use a static image as backgroun (white picture like the aquarios background
 - maybe I dont need to do frame differencing
 
 - i'm testing doing the cv with a smaller image and drawing the image from VideGrabber
 - It works not so good and I'm not sure if it computationally less demanding (cpu 74%, memory 98%).
 */


#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    camWidth = 1280;
	camHeight = 720;
    
    ROI.width = 1265; // set it to camWidth to have ROI = to camera size
    ROI.height = 390;// set it to camHeight to have ROI = to camera size
    ROI.x = 10; // set it to zero to get ROI = camwidth
    ROI.y = 330; // set it to zero to get ROI = camheight

    scaleRatio = 4;
    
#ifdef _USE_LIVE_VIDEO
    //we can now get back a list of devices.
	vector<ofVideoDevice> devices = vidGrabber.listDevices();
    
    for(int i = 0; i < devices.size(); i++){
		cout << devices[i].id << ": " << devices[i].deviceName;
        if( devices[i].bAvailable ){
            cout << endl;
        }else{
            cout << " - unavailable " << endl;
        }
	}
	vidGrabber.setDeviceID(1);
    
    //vidGrabber.setVerbose(true);  // check what this is!
    vidGrabber.initGrabber(camWidth,camHeight);
#else
    vidPlayer.loadMovie("test_animation.mov");
    vidPlayer.play();
#endif
    
    
    colorImg.allocate(camWidth, camHeight);
    grayTempImage.allocate(camWidth, camHeight);
    grayBg.allocate(ROI.width/scaleRatio, ROI.height/scaleRatio);

    
//    grayImage.allocate(camWidth, camHeight);
//    grayBg.allocate(camWidth/scaleRatio, camHeight/scaleRatio);

    
    
    //******** Selects the method for learning background ***********
	bLearnBakground = false; // learn from video ('space bar')
    bLoadPictureBakground = true; // load from picture file ('p' key)
    //***************************************************************
    
    
	threshold = 50;
    
    // ************ LINE DECLARATION **************
    firstLine.setCamSize(camWidth, camHeight);
    secondLine.setCamSize(camWidth, camHeight);
    
    firstLine.setStatus(true);
    firstLine.setThickness(5);
    
    secondLine.setStatus(true);
    secondLine.setThickness(5);
    // ********************************************

    
    ofSetFrameRate(15);
    
    
}



//--------------------------------------------------------------
void ofApp::update(){

	ofBackground(0,0,0);
    bool bNewFrame = false;
    
    // ************ LINE UPDATE **************
    firstLine.setCamSize(ROI.width, camHeight);
    secondLine.setCamSize(ROI.width, camHeight);
    // ********************************************

    
#ifdef _USE_LIVE_VIDEO
    vidGrabber.update();
    bNewFrame = vidGrabber.isFrameNew();
#else
    vidPlayer.update();
    bNewFrame = vidPlayer.isFrameNew();
#endif
    
    
    // Assigns a frame from the video/camera to a color image
	if (bNewFrame){
#ifdef _USE_LIVE_VIDEO
        colorImg.setFromPixels(vidGrabber.getPixels(), camWidth, camHeight);
  
#else
        colorImg.setFromPixels(vidPlayer.getPixels(), camWidth, camHeight);
#endif
    
        grayTempImage.clear();
        grayTempImage.allocate(camWidth, camHeight);
        grayTempImage = colorImg;
        grayTempImage.setROI(ROI);
      
        grayImage.clear();
        grayImage.allocate(ROI.width, ROI.height);
        grayImage.setFromPixels(grayTempImage.getRoiPixels(), ROI.width, ROI.height);
  //      grayImage.resize(camWidth/scaleRatio, camHeight/scaleRatio);
        grayImage.resize(ROI.width/scaleRatio, ROI.height/scaleRatio);
      
      
        

        
        //******** LEARN BACKGROUND (space bar) *******************
        if (bLearnBakground == true){
            grayBg.clear();
            grayBg.allocate(ROI.width/scaleRatio, ROI.height/scaleRatio);
            grayImage.scaleIntoMe(grayBg);
			grayBg = grayImage;
        
            bgImg.allocate(ROI.width/scaleRatio, ROI.height/scaleRatio, OF_IMAGE_GRAYSCALE);
            unsigned char * pixels = grayBg.getPixels();
            bgImg.setFromPixels(pixels, ROI.width/scaleRatio, ROI.height/scaleRatio, OF_IMAGE_GRAYSCALE);
            bgImg.saveImage("background-"+ofGetTimestampString()+".png");
            
            bLearnBakground = false;
            cout << "------------------" << endl;
            cout << "------------------" << endl; 
            cout << "CAPTURE BACKGROUNG" << endl;
            cout << "------------------" << endl;
            cout << "------------------" << endl;

		}
 
        
        //******** LOAD BACKGROUND PICTURE ('p' key) *******************
        if (bLoadPictureBakground == true){
            loader.loadImage("background.png");
            cout << "load image from file" << endl;
            loader.setImageType(OF_IMAGE_GRAYSCALE);
            loader.resize(ROI.width/scaleRatio, ROI.width/scaleRatio);
            cout << "resize image" << endl;
            grayBg.clear();
            grayBg.allocate(ROI.width/scaleRatio, ROI.height/scaleRatio);
            grayBg.setFromPixels(loader.getPixels(),ROI.width/scaleRatio, ROI.height/scaleRatio);
			bLoadPictureBakground = false;
		}
        

        
		// take the abs value of the difference between background and incoming and then threshold:
        grayDiff.clear();
        grayDiff.allocate(ROI.width/scaleRatio, ROI.height/scaleRatio);
		grayDiff.absDiff(grayBg, grayImage);
        grayDiff.threshold(threshold);
        
		// find co ntours which are between the size of 20 pixels and 1/3 the w*h pixels.
		// also, find holes is set to true so we will get interior contours as well....
        
        
		contourFinder.findContours(grayDiff, 1, (ROI.width/scaleRatio*ROI.height/scaleRatio/4), 1, false);	// find holes (it is computationally expensive!!)
        //addjust the value of the maximum blob size!

         }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
	// draw the incoming, the grayscale, the bg and the thresholded difference
	ofSetHexColor(0xffffff);
    
	//vidGrabber.draw(0, 0);
	colorImg.draw(((camWidth-ROI.width)*0.5)-ROI.x, ((camHeight-ROI.height)*0.5)-ROI.y);


    
    firstLine.drawLine();
    secondLine.drawLine();
    
    
    
    if (showCalibrationScreen) {
        ofSetHexColor(0xffffff);
        grayImage.draw(0, 0);
        ofNoFill();
        ofSetColor(255, 0, 0);
        ofColor(0, 255, 0);
        ofRect((camWidth-ROI.width)*0.5, (camHeight-ROI.height)*0.5, ROI.width, ROI.height);
    
        if (contourFinder.nBlobs > 0){
            contourFinder.blobs[0].draw(0, 0);
            
            ofSetColor(255, 0, 0);
            ofFill();
            ofCircle(contourFinder.blobs[0].centroid.x*scaleRatio+((camWidth-ROI.width)/2), contourFinder.blobs[0].centroid.y*scaleRatio+((camHeight-ROI.height)/2), 10);

            ofSetColor(0, 255, 0);
            ofCircle(contourFinder.blobs[0].centroid.x, contourFinder.blobs[0].centroid.y, 10);
            
            // ****** A report **********************
            ofSetHexColor(0xffffff);
            stringstream reportStr;
            reportStr << "bg subtraction and blob detection" << endl
            << "press ' ' to capture bg" << endl
            << "threshold " << threshold << " (press: +/-)" << endl
            << "num blobs found " << contourFinder.nBlobs << ", fps: " << ofGetFrameRate();
            
            ofDrawBitmapString(reportStr.str(), 20, 600);
            ofDrawBitmapString(ofToString(ofGetFrameRate()), 10, 10);
            // **************************************

        }
    }else{
        ofSetColor(0, 0, 0);
        ofFill();
        ofRect(0, 0, camWidth, (camHeight-ROI.height)/2);
        ofRect(0, ((camHeight-ROI.height)/2)+ROI.height, camWidth, camHeight);
        ofRect(0, 0, (camWidth-ROI.width)/2, camHeight);
        ofRect(((camWidth-ROI.width)/2)+ROI.width, 0, camWidth, camHeight);
    }
    
   
    
	   



}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
	switch (key){
		case ' ':
			bLearnBakground = true;
			break;
        case 'p': // loads the picture as learning background
			bLoadPictureBakground = true;
			break;
		case 'y':
			threshold ++;
			if (threshold > 255) threshold = 255;
			break;
		case 'r':
			threshold --;
			if (threshold < 0) threshold = 0;
			break;
        case 'o':
            ROI.width = ROI.width+5;
			break;
        case 'l':
            ROI.width = ROI.width-5;
 			break;
        case 'i':
            ROI.height = ROI.height+5;
			break;
        case 'k':
            ROI.height = ROI.height-5;
			break;

        case 'w':
            ROI.y = ROI.y-5;
			break;
        case 's':
            ROI.y = ROI.y+5;
			break;
        case 'a':
            ROI.x = ROI.x-5;
			break;
        case 'd':
            ROI.x = ROI.x+5;
			break;
        case 'z':
            showCalibrationScreen = !showCalibrationScreen;
			break;
        case 'q':
            cout <<"***************" << endl;
            cout << "GRAY BG: " << grayBg.width << " x " << grayBg.height << endl;
            cout << "GRAY IMG: " << grayImage.width << " x " << grayImage.height << endl;
            cout << "COLOR IMG: " << colorImg.width << " x " << colorImg.height << endl;
            cout << "GRAY TEMP: " << grayTempImage.width << " x " << grayTempImage.height << endl;
            cout << "ROI TEMP: " << grayTempImage.getROI().width << " x " << grayTempImage.getROI().height << endl;
            cout << "ROI x, y: " << grayTempImage.getROI().x << " , " << grayTempImage.getROI().y << endl << endl;
			break;
        }
}


//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
    firstLine.setVelocity(x / 100);
    secondLine.setVelocity(y / 100);
    
}
