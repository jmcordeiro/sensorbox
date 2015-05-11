//
//  soundInput.cpp
//  Sensor_box_kinect_v0.1
//
//  Created by Joao Cordeiro on 10/05/15.
//
//

#include "soundInput.h"


SoundInput::SoundInput(){

    
    soundStream.listDevices();
    
    //if you want to set a different device id
    soundStream.setDeviceID(2);
    
    int bufferSize = 256;
    
    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    
    smoothedVol = 0.0;
    
    soundStream.setup(this, 0, 2, 44100, bufferSize, 1);

}

SoundInput::~SoundInput(){
    soundStream.close();
}

float SoundInput::getSoundVolume(){
    return  smoothedVol*1000;
}



void SoundInput::audioIn(float * input, int bufferSize, int nChannels){
    
    float curVol = 0.0;
    // samples are "interleaved"
    int numCounted = 0;
    
    //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
    for (int i = 0; i < bufferSize; i++){
        left[i]		= input[i*2]*0.5;
        right[i]	= input[i*2+1]*0.5;
        
        curVol += left[i] * left[i];
        curVol += right[i] * right[i];
        numCounted+=2;
    }
    
    //this is how we get the mean of rms :)
    curVol /= (float)numCounted;
    
    // this is how we get the root of rms :)
    curVol = sqrt( curVol );
    
    smoothedVol *= 0.93;
    smoothedVol += 0.07 * curVol;
    
    
}