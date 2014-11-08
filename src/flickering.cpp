//
//  flickering.cpp
//  fish-cv_1
//
//  Created by Joao Cordeiro on 07/11/14.
//
//

#include "flickering.h"

int a = 0;
int firstFrame = 0;
int frameDif = 0;
void flickering(int x, int y, int w, int h, int t, int bpm){
    
    if ((ofGetFrameNum()%int(bpm*0.25)) == 0){
        firstFrame = ofGetFrameNum();
    }
    
    frameDif = ofGetFrameNum()-firstFrame;
    if (frameDif < 1) {
        ofSetColor(0, 0, 0, t*0.8);
    }else{
        ofSetColor(0, 0, 0, ofRandom(t*0.2, t*0.5));
    }
    ofRect(x, y, w, h);
};