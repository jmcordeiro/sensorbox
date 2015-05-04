//
//  liveFish.h
//  fish-cv_1
//
//  Created by Joao Cordeiro on 30/04/14.
//
//



#ifndef __fish_cv_1__liveFish__
#define __fish_cv_1__liveFish__

#include <iostream>
#include "ofMain.h"

class LiveFish{

    int paning;
    int paralaxX;
    int paralaxY;
    int canvasX;
    int canvasY;
    string oscMessage;
    unsigned long long newTime;
    ofVec2f fishPos_2;
    
    
public:
    LiveFish();
    ~LiveFish();
    void makeFishToWork(int _cX, int _cY, int _x, int _y, int _w, int _h, int _parX, int _parY, int _scaledOutput);

    int velocity;
    ofVec2f fishPos_1;

    int getVelocity();
    

};



#endif /* defined(__fish_cv_1__liveFish__) */


