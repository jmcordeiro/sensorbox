//
//  drawLine.cpp
//  fish_draw_line
//
//  Created by Joao Cordeiro on 25/04/14.
//
//

#include "drawLine.h"



Line::Line(){
    velocity = 1;
    opacity = 1;
    thickness = 1;
    xPosition = 0;
    yPosition = 0;
    isVertical = true;
    status = false;
    width = 1280;
    height = 720;
    reverse = false;
    xIniPos = 0;
    paralaxX = 0;
    lineSender.setup(HOST, PORT);


};

Line::~Line(){

};

void Line::drawLine(){
    
    if (status) {
        ofSetColor(0,0,255);    //set te color to blue
        ofSetLineWidth(thickness);
        ofLine(xPosition, yPosition, xPosition, height);
  
        if (xPosition >= width+xIniPos) reverse = true;
        if (xPosition <= 0+xIniPos) reverse = false;
        
        if (reverse) {
            xPosition = xPosition-velocity;
        }else{
        xPosition = xPosition+velocity;
        }
        
    }
    
    getLinePosition();
    
};

void Line::setStatus(bool _status){
    status = _status;
};

bool Line::getStatus(){
};


int Line::getLinePosition(){
    
    int linePos;
    linePos = (int) (xPosition-paralaxX)/(width/100);
    cout << "LINE POS: "<<linePos << endl;
    
    ofxOscMessage l1_p;
    l1_p.setAddress("/line_1_Pos");
    l1_p.addIntArg(linePos);
    lineSender.sendMessage(l1_p);
    
};

void Line::setVelocity(int _vel){
    velocity = _vel;
};

int Line::getVelocity(){
};

void Line::setOpacity(){
};

int Line::getOpacity(){
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

void Line::setCamSize(int _width, int _height, int _x, int _y){
    width = _width;
    height = _height+_y;
    xIniPos = _x;
    yPosition = _y;
    paralaxX = _x;
    
};

