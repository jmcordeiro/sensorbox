#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "liveFish.h"
#include "cells.h"
#include "gui.h"
#include "logger.h"
#include "arduino.h"
#include "soundInput.h"
#include "ofxBackground.h"


#define _USE_LIVE_VIDEO		// uncomment this to use a live camera
// otherwise, we'll use a movie file

// USE screen resolution of 1080 x 720 for ber displaying (720p)

class ofApp : public ofBaseApp{
    
    int decreases;
    int theCell;
    bool isNotMute;
    int toogleSounds;
    bool keyDown[255];
    int whichBackgroundImg;
    int numOfRows;
    int numOfColls;
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
    
    ofTrueTypeFont myfont;
	
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

    ofxBackground myBackgroundAddon;
    
    ofImage loader;
    ofImage bgImgDay;
    ofImage bgImgNight;
    ofImage bgImgDayStatic;
    ofImage bgImgNightStatic;

    
    int threshold;
    bool bLearnBakground, bLoadPictureBakground, bLearnBackground;
    bool blackFrame;

    
    
    SoundInput mySoundInput;

    
    LiveFish myFish;

    ofSoundPlayer sound_1;
    ofSoundPlayer sound_2;
    ofSoundPlayer sound_3;
    ofSoundPlayer sound_4;
    
    Gui myGui;
    Logger myLogger;
    Arduino myArduino;
    
};







