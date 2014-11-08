//
//  bubbles.h
//  fish-cv_1
//
//  Created by Joao Cordeiro on 09/11/14.
//
//

#ifndef __fish_cv_1__bubbles__
#define __fish_cv_1__bubbles__

#include <stdio.h>
#include "ofMain.h"

#include "demoParticle.h"


class Bubble: public demoParticle {

   // int bintensity;
public:
    
   // void setBintensity(int);
    Bubble();
    ~Bubble();
    
    void bubblesUpdate(ofVec2f);
    void bubblesDraw();
    
    particleMode bubblesMode;
    string bubblesModeStr;
    vector <demoParticle> bubbles;
    
    void resetParticles();
    void keyPressed(int key);
};



#endif /* defined(__fish_cv_1__bubbles__) */
