//
//  gui.h
//  fish-cv_sensor_box
//
//  Created by Joao Cordeiro on 29/04/15.
//
//

#ifndef __fish_cv_sensor_box__gui__
#define __fish_cv_sensor_box__gui__

#include <stdio.h>
#include "ofMain.h"
#include "ofxGui.h"


class Gui{

    ofxPanel sensorBoxGui;
    ofxFloatSlider vol_1;
    ofxFloatSlider vol_2;
    ofxFloatSlider vol_3;
    ofxFloatSlider vol_4;
    
public:
   
    Gui();
    ~Gui();
    
    void drawGui(int, int);
    float getVol_1();
    float getVol_2();
    float getVol_3();
    float getVol_4();

    
};



#endif /* defined(__fish_cv_sensor_box__gui__) */
