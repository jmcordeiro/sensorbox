//
//  fadeScreen.cpp
//  fish-cv_1
//
//  Created by Joao Cordeiro on 09/11/14.
//
//

#include "fadeScreen.h"



void fadeScreen(int intensity){
    ofSetColor(0, 0, 0, intensity);
    ofRect(0,0 , ofGetWindowWidth(), ofGetWindowHeight());
}


void fadeScreenToWhite(int intensity){
    ofSetColor(255, 255, 255, intensity);
    ofRect(0,0 , ofGetWindowWidth(), ofGetWindowHeight());
}
