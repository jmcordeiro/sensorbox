
//  cells.cpp
//  fish-cv_sensor_box
//
//  Created by Joao Cordeiro on 29/04/15.


#include "cells.h"

int cell;
int xOld;
int yOld;
int oldCell;
float dist;

// returns the number of te cell and draws a red grid and transparent square
int myCell(int pX, int pY, int w, int h, int rowNum, int collNum, int x, int y, bool fr){
    

    if (fr) {
        int cell = 0;
        int xOld = x;
        int yOld = y;
        int oldCell = cell;
        cout << "FIRST" << endl;
    };
    
    dist = ofDist(xOld, yOld, x, y);
    
    int fishRow = (y-pY)/(h/rowNum);       // the row where the fish is
    int fishColl = (x-pX)/(w/collNum);     // the collumn where the fish is
    int numCells = rowNum*collNum;         // total number of cells in the ROI
    int cellsW = w/collNum;                // the width if the cells (individual)
    int cellsH = h/rowNum;                 // the height of the cells (individual)
    cell = 1+collNum*fishRow+fishColl;     // the number of the cell where the fish is

    
    ofSetColor(255, 255, 255);
    
    if (dist < 50){
        xOld = x;
        yOld = y;
        oldCell = cell;
        cout << "dist: " << dist << endl;
        cout << "x: " << x << endl;
        cout << "y: " << y << endl;
        cout << "xOld: " << xOld << endl;
        cout << "yOld: " << yOld << endl;
        return cell;
        
    }else{
        xOld = x;
        yOld = y;
        cout << "dist_: " << dist << endl;
        return oldCell;
    }
    
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
    ofSetColor(255, 255, 255);

    ofDrawBitmapString(ofToString(dist), ofGetWidth()-50, 325);

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


