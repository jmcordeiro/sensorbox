//
//  rain.h
//  fish-cv_1
//
//  Created by Joao Cordeiro on 16/11/14.
//
//

#ifndef __fish_cv_1__rain__
#define __fish_cv_1__rain__

#include <stdio.h>
#include "ofMain.h"

#include "demoParticle.h"


class rain: public demoParticle {
    
public:
    
    int rintensity;
    int rainFreq;
    
    // void setBintensity(int);
    rain();
    ~rain();
    
    void rainUpdate(int, int);
    void rainDraw();
    
    particleMode rainMode;
    string rainModeStr;
    vector <demoParticle> raining;
    
    void resetParticles();
    void keyPressed(int key);
};




#endif /* defined(__fish_cv_1__rain__) */
