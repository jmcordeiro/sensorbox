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
    bintensity = 1;
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
 
    /*
    //lets add a bit of movement to the attract points
    for(unsigned int i = 0; i < attractPointsWithMovement.size(); i++){
        attractPointsWithMovement[i].x = attractPoints[i].x + ofSignedNoise(i * 10, ofGetElapsedTimef() * 0.7) * 12.0;
        attractPointsWithMovement[i].y = attractPoints[i].y + ofSignedNoise(i * -10, ofGetElapsedTimef() * 0.7) * 12.0;
    }
*/
    

};




//--------------------------------------------------------------
void Bubble::bubblesDraw(){
    for(unsigned int i = 0; i < bubbles.size(); i++){
        bubbles[i].draw();
    }
    
    ofSetColor(230);
    ofDrawBitmapString(bubblesModeStr + "\n\nSpacebar to reset. \nKeys 1-4 to change mode.", 10, 20);
};



/*
void Bubble::setBintensity(int i){
    bintensity = i;

}
*/



//--------------------------------------------------------------
void Bubble::resetParticles(){
    
  /*
    //these are the attraction points used in the forth demo
    attractPoints->clear();
    for(int i = 0; i < 4; i++){
        attractPoints->push_back( ofPoint( ofMap(i, 0, 4, 100, ofGetWidth()-100) , ofRandom(100, ofGetHeight()-100) ) );
    }
    
   // attractPointsWithMovement = attractPoints;
    
   */
    for(unsigned int i = 0; i < bubbles.size(); i++){
        bubbles[i].setMode(bubblesMode);
       // p[i].setAttractPoints(&attractPointsWithMovement);;
        bubbles[i].reset();
        
        
    }
    
}


