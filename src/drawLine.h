//
//  drawLine.h
//  fish_draw_line
//
//  Created by Joao Cordeiro on 25/04/14.
//
//

#ifndef __fish_draw_line__drawLine__
#define __fish_draw_line__drawLine__

#include <iostream>
#include "ofMain.h"

#include "ofxOsc.h"

#define HOST "localhost"
#define PORT 12345


class Line {
    int velocity;
    int opacity;
    int thickness;
    int xIniPos;
    int xPosition;
    int yPosition;
    bool isVertical;
    bool status;
    int width;
    int height;
    bool reverse;
    int paralaxX;
    ofxOscSender lineSender;
    
public:
    Line();
    ~Line();
    void drawLine();
    
    void setStatus(bool);
    bool getStatus();
    
    int getLinePosition();
    
    void setVelocity(int);
    int getVelocity();
    
    void setOpacity();
    int getOpacity();
    
    void setThickness(int);
    int getThickness();
    
    void setOrientation();
    bool getOrientation();
        
    void setCamSize(int _width, int _height, int _x, int _y);
    
};


#endif /* defined(__fish_draw_line__drawLine__) */
