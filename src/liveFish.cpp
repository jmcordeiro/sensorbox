//
//  liveFish.cpp
//  fish-cv_1
//
//  Created by Joao Cordeiro on 30/04/14.
//
//

#include "liveFish.h"

/*
 int fishXpos;
 int fishyYpos;
 int velocity;
 int paning;
 string oscMessage;
 */

LiveFish::LiveFish(){
    newTime = ofGetElapsedTimeMillis();
    fishPos_1 = ofVec2f(0 , 0);
    fishPos_2 = ofVec2f(0, 0);
    oscSenderFish.setup(HOST, PORT);
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
    
    getVelocity();
    getPosition(_scaledOutput);
    
}


// returns fish velocity and send it over OSC
int LiveFish::getVelocity(){
    
    // calculates velocity
    int distance = fishPos_2.squareDistance(fishPos_1);
    velocity = distance/(ofGetLastFrameTime()*50); // change this number for scling the velocity values
    fishPos_2 = ofVec2f(fishPos_1);

    // cout << "new velocity: " << velocity << endl;
    
  /*
    // Sends OSC Messagens (velocity)
    ofxOscMessage v, x, y;
    v.setAddress("/fishVelocity");
    v.addIntArg(velocity);
    oscSenderFish.sendMessage(v);
    */
    
 //   cout << "distance: " << velocity << endl;
    return velocity;
}


ofVec2f LiveFish::getPosition(int _scaledOutput){
   
    ofVec2f fishPosition;
    fishPosition = ofVec2f((int) (fishPos_1.x-paralaxX)/(canvasX/_scaledOutput), (int)(fishPos_1.y-paralaxY)/(canvasY/_scaledOutput));
    
    //cout << fishPosition.x << " - " << fishPosition.y << endl;
  
    /*
    // Sends OSC Messagens (velocity)
    ofxOscMessage p_x, p_y;
    p_x.setAddress("/fishX");
    p_x.addIntArg(fishPosition.x);
    oscSenderFish.sendMessage(p_x);

    p_y.setAddress("/fishY");
    p_y.addIntArg(fishPosition.y);
    oscSenderFish.sendMessage(p_y);
*/
    
    return fishPosition;
    
}





