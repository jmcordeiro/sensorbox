//
//  flickering.cpp
//  fish-cv_1
//
//  Created by Joao Cordeiro on 07/11/14.
//
//

#include "flickering.h"


void flickering(int x, int y, int w, int h, int t){
    
    ofColor(255, 0, 0, ofRandom(10));
    ofRect(x, y, w, h);
    
};