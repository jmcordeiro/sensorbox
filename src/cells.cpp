//
//  cells.cpp
//  fish-cv_sensor_box
//
//  Created by Joao Cordeiro on 29/04/15.
//
//

#include "cells.h"


int myCell(int pX, int pY, int w, int h, int rowNum, int collNum, int x, int y){

    int fishRow = y/(h/rowNum); // the row where the fish is
    int fishColl = x/(w/collNum); // the collumn where the fish is
    int numCells = rowNum*collNum; // total number of cells in the ROI
    int cellsW = w/collNum; // the width if the cells (individual)
    int cellsH = h/rowNum;  // the height of the cells (individual)
    int cell = collNum*fishRow+fishColl; // the number of the cell where the fish is
  
    
    // draw rectangles
    ofSetColor(255,0,0);
    ofNoFill();
    
    for (int i = 0; i<rowNum; i++) {
        for (int j=0; j<collNum; j++) {
            ofRect(j*cellsW, i*cellsH, cellsW, cellsH);
        }
    }
    
    
    return cell;
    
};

