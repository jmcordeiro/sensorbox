//
//  gui.cpp
//  fish-cv_sensor_box
//
//  Created by Joao Cordeiro on 29/04/15.
//
//

#include "gui.h"


Gui::Gui(){

    sensorBoxGui.setup();
    sensorBoxGui.add(vol_1.setup("Volume 1", 0.8, 0, 1));
    sensorBoxGui.add(vol_2.setup("Volume 2", 0.8, 0, 1));
    sensorBoxGui.add(vol_3.setup("Volume 3", 0.8, 0, 1));
    sensorBoxGui.add(vol_4.setup("Volume 4", 0.8, 0, 1));
    
}


Gui::~Gui(){
    
}

void Gui::drawGui(int x, int y){

    sensorBoxGui.setPosition(x, y);
    sensorBoxGui.draw();

}


float Gui::getVol_1(){
    return vol_1;
}

float Gui::getVol_2(){
    return vol_2;
}

float Gui::getVol_3(){
    return vol_3;
}

float Gui::getVol_4(){
    return vol_4;
}