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

    int fishXpos;
    int fishyYpos;
    int velocity;
    int paning;
    string oscMessage;
    unsigned long long newTime;
    ofVec2f fishPos_1;
    ofVec2f fishPos_2;
    ofxOscSender oscSenderFish;

    
public:
    LiveFish();
    ~LiveFish();
    void setFishPos(int _x, int _y);

    int getVelocity(float _x, float _y);
    ofVec2f ofgetPosition();
    
    void sendOsc();


};

#endif /* defined(__fish_cv_1__liveFish__) */


