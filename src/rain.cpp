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
    raining.assign(num, demoParticle());
    rainModeStr = "Raining";
    //   setBintensity(1);
    rintensity = 100;
    resetParticles();
    
};


rain::~rain(){
    
}

//--------------------------------------------------------------
void rain::rainUpdate(){
    
    //    rains.assign(bintensity, demoParticle());
    
    raining.resize(rintensity);
    
    for(unsigned int i = 0; i < raining.size(); i++){
        raining[i].setMode(rainMode);
        raining[i].update();
        //cout << "inside rains: " << rains[i].getFishPosPrt().x << endl;
    }
    
    /*
     //lets add a bit of movement to the attract points
     for(unsigned int i = 0; i < attractPointsWithMovement.size(); i++){
     attractPointsWithMovement[i].x = attractPoints[i].x + ofSignedNoise(i * 10, ofGetElapsedTimef() * 0.7) * 12.0;
     attractPointsWithMovement[i].y = attractPoints[i].y + ofSignedNoise(i * -10, ofGetElapsedTimef() * 0.7) * 12.0;
     }
     */
    
    
};




//--------------------------------------------------------------
void rain::rainDraw(){
    for(unsigned int i = 0; i < raining.size(); i++){
        raining[i].draw();
    }
    
    // ofSetColor(230);
    // ofDrawBitmapString(rainsModeStr + "\n\nSpacebar to reset. \nKeys 1-4 to change mode.", 10, 20);
};



/*
 void rain::setBintensity(int i){
 bintensity = i;
 
 }
 */



//--------------------------------------------------------------
void rain::resetParticles(){
    
    /*
     //these are the attraction points used in the forth demo
     attractPoints->clear();
     for(int i = 0; i < 4; i++){
     attractPoints->push_back( ofPoint( ofMap(i, 0, 4, 100, ofGetWidth()-100) , ofRandom(100, ofGetHeight()-100) ) );
     }
     
     // attractPointsWithMovement = attractPoints;
     
     */
    for(unsigned int i = 0; i < raining.size(); i++){
        raining[i].setMode(rainMode);
        // p[i].setAttractPoints(&attractPointsWithMovement);;
        raining[i].reset();
        
        
    }
    
}
