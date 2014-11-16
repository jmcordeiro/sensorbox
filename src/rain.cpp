//
//  rain.cpp
//  fish-cv_1
//
//  Created by Joao Cordeiro on 16/11/14.
//
//

#include "rain.h"

rain::rain(){
    int num = 15;
    rainMode = PARTICLE_MODE_RAIN;
    raining.assign(num, demoParticle(rintensity));
    rainModeStr = "Raining";
    // setBintensity(1);
    rainFreq = 0;
    rainIntensity = 0;
    resetParticles();
};

rain::~rain(){
}

//--------------------------------------------------------------
void rain::rainUpdate(int rIntUp, int rF){
    
    int countChanges = 0;
    countChanges = rF-raining.size();
    
    if (countChanges > 0) {
        for (int i = 0; i < countChanges; i++) {
            raining.push_back(demoParticle());
            raining.back().setMode(rainMode);
            raining.back().uniqueVal = ofRandom(-10000, 10000);
            raining.back().pos.x = ofRandom(-100, ofGetWidth());
            raining.back().pos.y = ofRandom(200,-400);
            raining.back().vel.x = 15;
            raining.back().vel.y = ofRandom(14, 18);
            raining.back().scale = 0.5;
        }
    }
    
    
    if (countChanges < 0) {
        for (int i = 0; i < abs(countChanges); i++) {
            raining.pop_back();
        }
    }
    
    
    for(unsigned int i = 0; i < raining.size(); i++){
        raining[i].setMode(rainMode);
        raining[i].rainIntensity = rIntUp;
        raining[i].update();
    }
};



//--------------------------------------------------------------
void rain::rainDraw(){
    for(unsigned int i = 0; i < raining.size(); i++){
        raining[i].draw();
    }
};



//--------------------------------------------------------------
void rain::resetParticles(){
    for(unsigned int i = 0; i < raining.size(); i++){
        raining[i].setMode(rainMode);
        raining[i].reset();
    }
}
