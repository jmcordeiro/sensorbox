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
    //   setBintensity(1);
    rintensity = 100;
    resetParticles();
};

rain::~rain(){
}

//--------------------------------------------------------------
void rain::rainUpdate(int rIntUp){
    
    //    rains.assign(bintensity, demoParticle());
    
    raining.resize(rintensity);
    
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
