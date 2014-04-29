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
    
    ROI.width = camWidth;
    ROI.height = camHeight;
    ROI.x = 0;
    ROI.y = 0;

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
    
//    grayImage.allocate(camWidth, camHeight);
//    grayBg.allocate(camWidth/scaleRatio, camHeight/scaleRatio);

    
    /*
    // This is used for analysing a smaller image
    grayImage.allocate(320, 180); // one gray image
    grayBg.allocate(320, 180);
	grayDiff.allocate(320, 180);
    */
    
    /*
     // This is used for analizing HD video
     grayImage.allocate(1280, 720);
     grayBg.allocate(1280, 720);
     grayDiff.allocate(1280, 720);
     */
    
    //******** Selects the method for learning background ***********
	bLearnBakground = true; // learn from video ('space bar')
    bLoadPictureBakground = false; // load from picture file ('p' key)
    //***************************************************************
    
    
	threshold = 80;
    
    

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
    
      
        grayTempImage.allocate(camWidth, camHeight);
        grayTempImage = colorImg;
        grayTempImage.setROI(ROI);
        cout << "COLOR IMG: " << colorImg.width << " x " << colorImg.height << endl;
        cout << "GRAY TEMP: " << grayTempImage.width << " x " << grayTempImage.height << endl;
        cout << "ROI TEMP: " << grayTempImage.getROI().height << " x " << grayTempImage.getROI().width << endl;
        
        grayImage.clear();
        grayImage.allocate(ROI.width, ROI.height);
        grayImage.setFromPixels(grayTempImage.getRoiPixels(), ROI.width, ROI.height);
        grayImage.resize(camWidth/scaleRatio, camHeight/scaleRatio);
      
        grayTempImage.clear();

        
        //******** LEARN BACKGROUND (space bar) *******************
        if (bLearnBakground == true){
			grayBg = grayImage;
            bLearnBakground = false;
		}
        
        //******** LOAD BACKGROUND PICTURE ('p' key) *******************
        if (bLoadPictureBakground == true){
            loader.loadImage("backgd_1.jpg");
            loader.setImageType(OF_IMAGE_GRAYSCALE);
            loader.resize(camWidth/scaleRatio, camHeight/scaleRatio);
            grayBg.setFromPixels(loader.getPixels(),loader.getWidth(), loader.getHeight());
			bLoadPictureBakground = false;
		}
        
     //   cout << "GRAY BG: " << grayBg.width << " x " << grayBg.height << endl;
     //   cout << "GRAY Image: " << grayImage.width << " x " << grayImage.height << endl;
		// take the abs value of the difference between background and incoming and then threshold:
		grayDiff.absDiff(grayBg, grayImage);
        grayDiff.threshold(threshold);
        
		// find co ntours which are between the size of 20 pixels and 1/3 the w*h pixels.
		// also, find holes is set to true so we will get interior contours as well....
        
        
		contourFinder.findContours(grayDiff, 1, (320*180), 1, false);	// find holes (it is computationally expensive!!)
        //addjust the value of the maximum blob size!

      
         }
         
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
	// draw the incoming, the grayscale, the bg and the thresholded difference
	ofSetHexColor(0xffffff);
    
	//vidGrabber.draw(0, 0);
    
	colorImg.draw(0,0);
    //grayImageTest.draw(0, 0);
    
  //  grayImage.draw(320, 0);
	//grayBg.draw(320*2,0);
    
 //   grayDiff.draw(320*3,0);
    
	// then draw the contours:
    
    //	ofFill();
    //	ofSetHexColor(0x333333);
    //	ofRect(360,540,320,240);
    //	ofSetHexColor(0xffffff);
    
	// we could draw the whole contour finder
	//contourFinder.draw(0, 0);
    
    
    /*	// or, instead we can draw each blob individually from the blobs vector,
     // this is how to get access to them:
     for (int i = 0; i < contourFinder.nBlobs; i++){
     contourFinder.blobs[i].draw(0, 0);
     
     // draw over the centroid if the blob is a hole
     ofSetColor(255);
     if(contourFinder.blobs[i].hole){
     ofDrawBitmapString("hole",
     contourFinder.blobs[i].boundingRect.getCenter().x,
     contourFinder.blobs[i].boundingRect.getCenter().y);
     }
     }
     */
    
    if (contourFinder.nBlobs > 0){
        contourFinder.blobs[0].draw(0, 0);
        ofSetColor(255, 0, 0);
        ofCircle(contourFinder.blobs[0].centroid.x*4, contourFinder.blobs[0].centroid.y*4, 10);
    }
    
	// finally, a report:
	ofSetHexColor(0xffffff);
	stringstream reportStr;
	reportStr << "bg subtraction and blob detection" << endl
    << "press ' ' to capture bg" << endl
    << "threshold " << threshold << " (press: +/-)" << endl
    << "num blobs found " << contourFinder.nBlobs << ", fps: " << ofGetFrameRate();
    
	
    ofDrawBitmapString(reportStr.str(), 20, 600);
    ofDrawBitmapString(ofToString(ofGetFrameRate()), 10, 10);
    
    firstLine.drawLine();
    secondLine.drawLine();

    if (showCalibrationScreen) {
    ofSetHexColor(0xffffff);
    grayImage.draw(0, 0);
    ofNoFill();
    ofSetColor(255, 0, 0);
    ofRect(ROI);
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
        case 'u':
            ROI.width = ROI.width+1;
			break;
        case 'j':
            ROI.width = ROI.width-1;
			break;
        case 'i':
            ROI.height = ROI.height+1;
			break;
        case 'k':
            ROI.height = ROI.height-1;
			break;
        case 'w':
            ROI.y = ROI.y-1;
			break;
        case 's':
            ROI.y = ROI.y+1;
			break;
        case 'a':
            ROI.x = ROI.x-1;
			break;
        case 'd':
            ROI.x = ROI.x+1;
			break;
        case 'z':
            showCalibrationScreen = !showCalibrationScreen;
			break;


        }
}


//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
    firstLine.setVelocity(x / 100);
    secondLine.setVelocity(y / 100);
    
}
