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
    
    
    camWidth 		= 1280;	// try to grab at this size.
    //	camHeight 		= 720;
    camHeight 		= 320;
    
    
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
    
    //  vidGrabber.setVerbose(true);  // check what this is!
    vidGrabber.initGrabber(camWidth,camHeight);
#else
    vidPlayer.loadMovie("test_animation.mov");
    vidPlayer.play();
#endif
    
    
    colorImg.allocate(1280, 720); // one color image
    colorImgSmall.allocate(1280, 720); // second color image
    
    // This is used for analysing a smaller image
    grayImage.allocate(320, 180); // one gray image
    grayBg.allocate(320, 180);
	grayDiff.allocate(320, 180);
    
    /*
     // This is used for analizing HD video
     grayImage.allocate(1280, 720);
     grayBg.allocate(1280, 720);
     grayDiff.allocate(1280, 720);
     */
    
    //******** Selects the method for learning background ***********
	bLearnBakground = false; // learn from video ('space bar')
    bLoadPictureBakground = true; // load from picture file ('p' key)
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

/// testing commiting GIT HUB

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
        colorImg.setFromPixels(vidGrabber.getPixels(), 1280, 720);
#else
        colorImg.setFromPixels(vidPlayer.getPixels(), 1280, 720);
#endif
        
        
        colorImgSmall.resize(1280, 720);
        colorImgSmall = colorImg;
        colorImgSmall.resize(320, 180);
        grayImage = colorImgSmall;
        
        
        if (bLearnBakground == true){
			grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
			bLearnBakground = false;
		}
        
        
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
    
    grayImage.draw(320, 0);
	grayBg.draw(320*2,0);
    
    grayDiff.draw(320*3,0);
    
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
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
    firstLine.setVelocity(x / 100);
    secondLine.setVelocity(y / 100);
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
