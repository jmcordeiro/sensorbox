//
//  soundInput.h
//  Sensor_box_kinect_v0.1
//
//  Created by Joao Cordeiro on 10/05/15.
//
//

#ifndef __Sensor_box_kinect_v0_1__soundInput__
#define __Sensor_box_kinect_v0_1__soundInput__

#include <stdio.h>
#include <iostream>
#include "ofMain.h"

class SoundInput: public ofBaseApp{
    
    void audioIn(float * input, int bufferSize, int nChannels);
    
    vector <float> left;
    vector <float> right;
    
    float smoothedVol;
    ofSoundStream soundStream;

    
public:
    SoundInput();
    ~SoundInput();

    float getSoundVolume();
    
};


#endif /* defined(__Sensor_box_kinect_v0_1__soundInput__) */
