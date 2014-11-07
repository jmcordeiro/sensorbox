#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "drawLine.h"
#include "liveFish.h"
#include "flickering.h"

#include "ofxGpuParticles.h"
#include "particlesSqr.h"

#define _USE_LIVE_VIDEO		// uncomment this to use a live camera
// otherwise, we'll use a movie file


class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void mouseMoved(int x, int y );

    
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
    
    Line firstLine;
    Line secondLine;
    
    LiveFish myFish;
    
    ParticlesSqr PrtBubbles;
    
    
    //******** THIS IS FOR THE PARTICLES **********
    // set any update uniforms in this function
    void onParticlesUpdate(ofShader& shader);
    
    ofxGpuParticles particles;
    ofEasyCam cam;
        //******** THIS IS FOR THE PARTICLES **********
    
    
    
};





