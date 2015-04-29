//
//  logger.cpp
//  fish-cv_sensor_box
//
//  Created by Joao Cordeiro on 29/04/15.
//
//

#include "logger.h"
#include <iostream>
#include <fstream>



Logger::Logger(){

    string tempName = ofGetTimestampString();
    logFile.open(ofToDataPath("logs/" + tempName + ".txt")); //file doesn't exist yet
    logFile.create(); // now file exists
    logFile.open(ofToDataPath("logs/" + tempName + ".txt"), ofFile::Append, ofFile::WriteOnly); //file doesn't exist yet

    //writes a header
    if (logFile.is_open()) {
        logFile
        << "timestamp"
        <<"*"
        << "milisenconds"
        <<"*"
        << "sound"
        <<"*"
        << "velocity"
        <<"*"
        << "Xposition"
        <<"*"
        << "Yposition"
        <<"*"
        << "SPL"
        <<"*"
        << "temperature"
        <<endl;
    }
    
    // control log on the console (just to be sure the file is open
    if (logFile.is_open()){
        cout << "is open" << endl;
    }else{
        cout << "is NOT open" << endl;
    };
    
}

Logger::~Logger(){
    logFile.close();
}

//which square, velocity, position, spl, temp;
void Logger::listenAndSendOneReading(int cell, int vel, int x, int y, float spl, float temp){
    if (logFile.is_open()) {
        logFile
        << ofGetTimestampString()
        <<"*"
        << ofGetElapsedTimeMillis()
        <<"*"
        << cell // file/quadrant
        <<"*"
        << vel // velocity
        <<"*"
        << x // YPosition
        <<"*"
        << y // YPosition
        <<"*"
        << spl // SPL
        <<"*"
        << temp // temp
        <<endl;
//        logFile.flush();
    }
}



bool Logger::getFileIsOpen(){
    return logFile.is_open();
}