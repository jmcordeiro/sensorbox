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
    fishXpos = 0;
    fishyYpos = 0;
    fishPos_1 = ofVec2f(0 , 0);
    fishPos_2 = ofVec2f(0, 0);
    oscSenderFish.setup(HOST, PORT);


}


LiveFish::~LiveFish(){
}

void LiveFish::setFishPos(int _x, int _y){
    fishXpos = _x;
    fishyYpos = _y;
}

// returns fish velocity and send it over OSC
int LiveFish::getVelocity(float _x, float _y){
    fishPos_1 = ofVec2f(_x, _y);
    
    int distance = fishPos_2.squareDistance(fishPos_1);
    newTime = ofGetElapsedTimeMillis()-newTime;
    velocity = distance/(newTime*0.0001);
    fishPos_2 = ofVec2f(fishPos_1);
 
    ofxOscMessage v, x, y;
    v.setAddress("/fishVelocity");
    v.addIntArg(velocity);
    oscSenderFish.sendMessage(v);

    x.setAddress("/fishX");
    x.addIntArg(_x); // change this to propprtional values (example:
    oscSenderFish.sendMessage(x);

    y.setAddress("/fishY");
    y.addIntArg(_y);
    oscSenderFish.sendMessage(y);

    
    return velocity;
}


ofVec2f LiveFish::ofgetPosition(){
    
}

void LiveFish::sendOsc(){

}
