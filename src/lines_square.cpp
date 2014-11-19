//
//  lines_square.cpp
//  fish-cv_1
//
//  Created by Joao Cordeiro on 11/11/14.
//
//

#include "lines_square.h"


int lineSquare(int lineLowX, int lineHiX, int lineLowInt, int lineHiInt, int opacity){
    int rectSize;
    
    ofSetColor(0, 0, 0, opacity);
    if (lineLowX < lineHiX){
        ofRect(lineLowX, 0, lineHiX-lineLowX, ofGetHeight());
        //rectSize = lineLowX-(lineHiX-lineLowX);
    }else if (lineLowX > lineHiX){
        ofRect(lineHiX, 0, lineLowX-lineHiX, ofGetHeight());
        //rectSize = lineHiX-(lineLowX-lineHiX);
    } else{
        ofLine(lineLowX, 0, lineLowX, ofGetHeight());
       // rectSize = 0;
    }
    rectSize = abs(lineLowX-lineHiX);
    return rectSize;
}