//
//  flickering.cpp
//  fish-cv_1
//
//  Created by Joao Cordeiro on 07/11/14.
//
//

#include "flickering.h"

int a = 0;

void flickering(int x, int y, int w, int h, int t){
    
    if (ofGetFrameNum()%2== 0){
        a = ofRandom(t);
    }
    
    
    ofSetColor(0, 0, 0, a);

    ofRect(x, y, w, h);
};