//
//  liveFish.cpp
//  fish-cv_1
//
//  Created by Joao Cordeiro on 30/04/14.
//
//

#include "liveFish.h"



LiveFish::LiveFish(){
    newTime = ofGetElapsedTimeMillis();
    fishPos_1 = ofVec2f(0 , 0);
    fishPos_2 = ofVec2f(0, 0);
    velocity = 1;
}


LiveFish::~LiveFish(){
}

void LiveFish::makeFishToWork(int _cX, int _cY, int _x, int _y, int _w, int _h, int _parX, int _parY, int _scaledOutput){
   
    fishPos_1 = ofVec2f(_x, _y);
    canvasX = _w;
    canvasY = _h;
    paralaxX = _parX;
    paralaxY = _parY;
    
}


// returns fish velocity
int LiveFish::getVelocity(){
    
    // calculates velocity
    int distance = fishPos_2.squareDistance(fishPos_1);
    velocity = distance/(ofGetLastFrameTime()*1000); // change this number for scaling the velocity values
    fishPos_2 = ofVec2f(fishPos_1);

    return velocity;
}






