//
//  arduino.cpp
//  fish-cv_sensor_box
//
//  Created by Joao Cordeiro on 30/04/15.
//
//

#include "arduino.h"


Arduino::Arduino(){
        mySerial.setup(0, 9600); // update port no and baud rate according to your system.
};

Arduino::~Arduino(){
};


void Arduino::readFromArduino(){
    string str;
    str = ofxGetSerialString(mySerial,'\n'); //read until end of line
    if (str[0] == 'h'){
        str.erase(0,1);
        humidity = ofToFloat(str);
    }
    if (str[0] == 't'){
        str.erase(0,1);
        temperature = ofToFloat(str);
    }

  }


string Arduino::ofxGetSerialString(ofSerial &serial, char until) {
    static string str;
    stringstream ss;
    char ch;
    int ttl=1000;
    while ((ch=serial.readByte())>0 && ttl>0 && ch!=until) {
        ss << ch;
    }
    str+=ss.str();
    
    if (ch==until) {
        string tmp=str;
        str="";
        return ofToString(tmp);
    } else {
        return "";
    }
}


float Arduino::getTemp(){
    return temperature;
}

float Arduino::getHum(){
    return humidity;
}