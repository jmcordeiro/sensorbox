//
//  bubbles.cpp
//  fish-cv_1
//
//  Created by Joao Cordeiro on 09/11/14.
//
//

#include "bubbles.h"


Bubble::Bubble(){
    int num = 15;
    bubbles.assign(num, demoParticle());
    bubblesMode = PARTICLE_MODE_NOISE;
    bubblesModeStr = "Breathing";
 //   setBintensity(1);
    bintensity = 255;
    resetParticles();
    
};


Bubble::~Bubble(){

}

//--------------------------------------------------------------
void Bubble::bubblesUpdate(ofVec2f xy){

//    bubbles.assign(bintensity, demoParticle());
    
    bubbles.resize(bintensity);
    
    for(unsigned int i = 0; i < bubbles.size(); i++){
        bubbles[i].setFishPosPrt(xy);
        bubbles[i].setMode(bubblesMode);
        bubbles[i].update();
        //cout << "inside bubbles: " << bubbles[i].getFishPosPrt().x << endl;
    }
};




//--------------------------------------------------------------
void Bubble::bubblesDraw(){
    for(unsigned int i = 0; i < bubbles.size(); i++){
        bubbles[i].draw();
    }
    
};




//--------------------------------------------------------------
void Bubble::resetParticles(){
    for(unsigned int i = 0; i < bubbles.size(); i++){
        bubbles[i].setMode(bubblesMode);
        bubbles[i].reset();
    }
    
}


