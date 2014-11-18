#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxMidi.h"
#include "ofxPostProcessing.h"
#include "ofxPostGlitch.h"


#include "drawLine.h"
#include "liveFish.h"
//#include "demoParticle.h"
#include "fadeScreen.h"
#include "flickering.h"
#include "bubbles.h"
#include "setupMidi.h"
#include "lines_square.h"
#include "rain.h"

//#define _USE_LIVE_VIDEO		// uncomment this to use a live camera
// otherwise, we'll use a movie file

// USE screen resolution of 1080 x 720 for ber displaying (720p)

class ofApp : public ofBaseApp, public ofxMidiListener{
    
    bool showMidi = false;
    
public:
    int masterBpm;  // (should convert to private!!)
    int flickIntensity;  // (should convert to private!!)
    int fadeScreenIntensity;  // (should convert to private!!)
    int fadeScreenIntensityWhite;  // (should convert to private!!)
    int lineHiVel; // (should convert to private!!)
    int lineLowVel;  // (should convert to private!!)
    int rectOpacity;  // should be bla bla bla
    int rainInt; // should bla bla
    int rainF; // should bla bla
    int prtInt;
    
    void setup();
    void update();
    void draw();
    
    void keyReleased(int key);
    void keyPressed(int key);
    void mouseMoved(int x, int y );
    void resetParticles();
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
    
    Line * firstLine = new Line;
    Line * secondLine = new Line;
    
    LiveFish myFish;

    Bubble fishBreath;
    rain myRain;

    ofFbo myFbo;
    ofxPostGlitch myGlitch;
    
    //*********** Template Prt ***************
    particleMode currentMode;
    string currentModeStr;
    vector <demoParticle> p;
    vector <ofPoint> attractPoints;
    vector <ofPoint> attractPointsWithMovement;

    //******** MIDI STUFF *****************
    void newMidiMessage(ofxMidiMessage& eventArgs);
    stringstream text;
    ofxMidiIn midiIn;
    ofxMidiMessage midiMessage;

    ofxPostProcessing fishFx;
    
    ofxMidiOut midiOut;
    ofxMidiMessage midiOutMsg;
};





