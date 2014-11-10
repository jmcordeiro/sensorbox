//
//  drawLine.cpp
//  fish_draw_line
//
//  Created by Joao Cordeiro on 25/04/14.
//
//

#include "drawLine.h"



Line::Line(){
    velocity = 0;
    opacity = 1;
    thickness = 1;
    xPosition = 0;
    yPosition = 0;
   // isVertical = true;
   // status = false;
    reverse = false;
  //  xIniPos = 0;
  //  lineSender.setup(HOST, PORT);


};

Line::~Line(){

};

void Line::lineUpdate(int vel, int intensity){
    if (xPosition >= ofGetWindowWidth()) reverse = true;
    if (xPosition <= 0) reverse = false;
    
    if (reverse) {
        xPosition = xPosition-vel;
    }else{
        xPosition = xPosition+vel;
    }
}


void Line::drawLine(){
        ofSetColor(0, 0, 0, opacity);
        ofLine(xPosition, 0, xPosition, ofGetHeight());
};


void Line::setStatus(bool _status){
    status = _status;
};

bool Line::getStatus(){
};


int Line::getLinePosition(){
    
   // int linePos;
   // linePos = (int) (xPosition-paralaxX)/(width/100);
    //cout << "LINE POS: "<<linePos << endl;
   
    /*
    ofxOscMessage l1_p;
    l1_p.setAddress("/line_1_Pos");
    l1_p.addIntArg(linePos);
    lineSender.sendMessage(l1_p);
    */
    
    return xPosition;
    
};

void Line::setVelocity(int _vel){
 //   velocity = _vel;
};

int Line::getVelocity(){
};

void Line::setOpacity(int o){
    opacity = o;
};

int Line::getOpacity(){
    return opacity;
};

void Line::setThickness(int _thickness){
    ofSetLineWidth(_thickness);
};

int Line::getThickness(){
};

void Line::setOrientation(){
};

bool Line::getOrientation(){
};


