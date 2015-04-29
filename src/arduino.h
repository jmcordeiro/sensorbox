//
//  arduino.h
//  fish-cv_sensor_box
//
//  Created by Joao Cordeiro on 30/04/15.
//
//

#ifndef __fish_cv_sensor_box__arduino__
#define __fish_cv_sensor_box__arduino__

#include <stdio.h>
#include "ofMain.h"
#include <string>

class Arduino{

    ofSerial mySerial;
    float temperature;
    float humidity;
    
public:

    Arduino();
    ~Arduino();

    void readFromArduino();
    string ofxGetSerialString(ofSerial &serial, char until);
    float getTemp();
    float getHum();

};

#endif /* defined(__fish_cv_sensor_box__arduino__) */
