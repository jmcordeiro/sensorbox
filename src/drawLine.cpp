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
    isVertical = true;
    status = false;
    width = 1280;
    height = 720;
    reverse = false;
};

Line::~Line(){
};

void Line::drawLine(){
    
    if (status) {
        ofSetColor(0,0,255);    //set te color to blue
        ofSetLineWidth(thickness);
        ofLine(xPosition, 0, xPosition, height);
  
        if (xPosition >= width) reverse = true;
        if (xPosition <= 0) reverse = false;
        
        if (reverse) {
            xPosition = xPosition-velocity;
        }else{
        xPosition = xPosition+velocity;
        }
        
    }
    
    
};

void Line::setStatus(bool _status){
    status = _status;
};

bool Line::getStatus(){
};

int Line::getXposition(){
};

int Line::getYposition(){
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

void Line::setCamSize(int _width, int _height){
    width = _width;
    height = _height;
};

