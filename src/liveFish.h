//
//  liveFish.h
//  fish-cv_1
//
//  Created by Joao Cordeiro on 30/04/14.
//
//

/*

 variables:
 x;
 y;
 velocity;
 paning;
 oscMessage;
 
 Methods:
 getVelocity();
 getPosition();
 sendOsc();
 
 
 
 */


#ifndef __fish_cv_1__liveFish__
#define __fish_cv_1__liveFish__

#include <iostream>
#include "ofMain.h"
#include "ofxOsc.h"

#define HOST "localhost"
#define PORT 12345


class LiveFish{

    int paning;
    int paralaxX;
    int paralaxY;
    int canvasX;
    int canvasY;
    string oscMessage;
    unsigned long long newTime;
    ofVec2f fishPos_2;
    ofxOscSender oscSenderFish;
    

    
public:
    LiveFish();
    ~LiveFish();
    void makeFishToWork(int _cX, int _cY, int _x, int _y, int _w, int _h, int _parX, int _parY, int _scaledOutput);

    int velocity;
    ofVec2f fishPos_1;

    int getVelocity();
    ofVec2f getPosition(int _scaledOutput);
    

};

#endif /* defined(__fish_cv_1__liveFish__) */


