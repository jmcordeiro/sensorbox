//
//  logger.h
//  fish-cv_sensor_box
//
//  Created by Joao Cordeiro on 29/04/15.
//
//

#ifndef __fish_cv_sensor_box__logger__
#define __fish_cv_sensor_box__logger__

#include <stdio.h>
#include "ofMain.h"



class Logger{
    
    ofFile logFile;

public:
    Logger();
    ~Logger();
    void listenAndSendOneReading();
    bool getFileIsOpen();

};


#endif /* defined(__fish_cv_sensor_box__logger__) */

