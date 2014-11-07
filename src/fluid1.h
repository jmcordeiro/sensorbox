//
//  fluid1.h
//  fish-cv_1
//
//  Created by Joao Cordeiro on 07/11/14.
//
//

 #pragma once
#ifndef __fish_cv_1__fluid1__
#define __fish_cv_1__fluid1__

#include <iostream>
#include "ofxFluid.h"
#include "ofMain.h"


class FluidClass {
    // variables go here
    
    
public:

    FluidClass();
    ~FluidClass();

    void fluidUpdate(int w, int h);
    void fluidDraw();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofxFluid fluid;
    ofBlendMode blendmode;
    
    ofVec2f oldM;
    int     width,height;
    bool    bPaint, bObstacle, bBounding, bClear;
  
    
};




#endif /* defined(__fish_cv_1__fluid1__) */
