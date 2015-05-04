//
//  cells.h
//  fish-cv_sensor_box
//
//  Created by Joao Cordeiro on 29/04/15.
//
//

#ifndef __fish_cv_sensor_box__cells__
#define __fish_cv_sensor_box__cells__

#include <stdio.h>
#include <iostream>
#include "ofxOsc.h"


int myCell(int pX, int pY, int w, int h, int rowNum, int collNum, int x, int y);
void myCellDraw(int pX, int pY, int w, int h, int rowNum, int collNum, int x, int y);


void drawGridCell(int pX, int pY, int w, int h, int rowNum, int collNum);


#endif /* defined(__fish_cv_sensor_box__cells__) */
