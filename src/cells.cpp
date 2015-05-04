//
//  cells.cpp
//  fish-cv_sensor_box
//
//  Created by Joao Cordeiro on 29/04/15.
//
//

#include "cells.h"


// returns the number of te cell and draws a red grid and transparent square
int myCell(int pX, int pY, int w, int h, int rowNum, int collNum, int x, int y){

    int fishRow = (y-pY)/(h/rowNum);        // the row where the fish is
    int fishColl = (x-pX)/(w/collNum);      // the collumn where the fish is
    int numCells = rowNum*collNum;          // total number of cells in the ROI
    int cellsW = w/collNum;                 // the width if the cells (individual)
    int cellsH = h/rowNum;                  // the height of the cells (individual)
    int cell = 1+collNum*fishRow+fishColl;    // the number of the cell where the fish is
  
    return cell;
};


// draw the red cell where the fish is
void myCellDraw(int pX, int pY, int w, int h, int rowNum, int collNum, int x, int y){

    int fishRow = (y-pY)/(h/rowNum);        // the row where the fish is
    int fishColl = (x-pX)/(w/collNum);      // the collumn where the fish is
    int cellsW = w/collNum;                 // the width if the cells (individual)
    int cellsH = h/rowNum;                  // the height of the cells (individual)

    for (int i = 0; i<rowNum; i++) {
        for (int j=0; j<collNum; j++) {
            if(fishRow == i && fishColl == j){
                ofSetColor(255,0,0,50);
                ofFill();
            }else{
                ofSetColor(255,0,0);
                ofNoFill();
            }
            ofRect(pX+j*cellsW, pY+i*cellsH, cellsW, cellsH);
        }
    }
}



// draws a white grid
void drawGridCell(int pX, int pY, int w, int h, int rowNum, int collNum){
    
    int numCells = rowNum*collNum;          // total number of cells in the ROI
    int cellsW = w/collNum;                 // the width if the cells (individual)
    int cellsH = h/rowNum;                  // the height of the cells (individual)
    
    ofSetColor(255,255,255);
    ofNoFill();
    
    for (int i = 0; i<rowNum; i++) {
        for (int j=0; j<collNum; j++) {
            ofRect(pX+j*cellsW, pY+i*cellsH, cellsW, cellsH);
        }
    }
    
};


