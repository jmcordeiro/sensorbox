#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
//#include "ofxMidi.h"
//#include "ofxPostProcessing.h"
//#include "ofxPostGlitch.h"


//#include "drawLine.h"
#include "liveFish.h"
//#include "demoParticle.h"
//#include "fadeScreen.h"
//#include "flickering.h"
//#include "bubbles.h"
//#include "setupMidi.h"
//#include "lines_square.h"
//#include "rain.h"

#define _USE_LIVE_VIDEO		// uncomment this to use a live camera
// otherwise, we'll use a movie file

// USE screen resolution of 1080 x 720 for ber displaying (720p)

class ofApp : public ofBaseApp{
    
    
public:
    int prtInt;
    
    void setup();
    void update();
    void draw();
    
    void keyReleased(int key);
    void keyPressed(int key);
    void mouseMoved(int x, int y );
    void exit();

    
#ifdef _USE_LIVE_VIDEO
    ofVideoGrabber 		vidGrabber;
#else
    ofVideoPlayer 		vidPlayer;
#endif
    
	
    int camWidth;
    int camHeight;
    int scaleRatio;
    int paralax_x;
    int paralax_y;
    
    ofVec2f fishPosBig, fishPosSmall;
     
    ofRectangle ROI;
    
    ofxCvColorImage			colorImg, colorImgSmall;
    ofxCvGrayscaleImage 	grayImage;
    ofxCvGrayscaleImage 	grayBg;
    ofxCvGrayscaleImage 	grayDiff;
    ofxCvGrayscaleImage 	grayTempImage;

    ofxCvContourFinder 	contourFinder;
    
    ofImage loader;
    
    int threshold;
    bool bLearnBakground, bLoadPictureBakground;
    bool showCalibrationScreen;

    ofImage bgImg;
    
    LiveFish myFish;
    
    ofSoundPlayer mySound;


};







