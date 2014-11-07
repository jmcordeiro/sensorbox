//
//  fluid1.cpp
//  fish-cv_1
//
//  Created by Joao Cordeiro on 07/11/14.
//
//

#include "fluid1.h"


FluidClass::FluidClass(){
    
  //  ofEnableAlphaBlending();
   // ofEnableBlendMode(OF_BLENDMODE_ADD);

    ofSetCircleResolution(100);
    
    width = 300;
    height = 600;
    
    // Initial Allocation
    //
    fluid.allocate(width, height, 0.5);
    
    // Seting the gravity set up & injecting the background image
    //
    fluid.dissipation = 0.99;
    fluid.velocityDissipation = 0.99;
    
    fluid.setGravity(ofVec2f(0.0,0.0));
    //    fluid.setGravity(ofVec2f(0.0,0.0098));
    
    //  Set obstacle
    //
    fluid.begin();
    ofSetColor(0,0);
    ofSetColor(0);
    ofCircle(width*0.5, height*0.35, 40);
    fluid.end();
    fluid.setUseObstacles(false);
    
    // Adding constant forces
    //
    fluid.addConstantForce(ofPoint(width*0.5,height*0.85), ofPoint(0,-2), ofFloatColor(0.5,0.1,0.0), 10.f);
    
    ofSetWindowShape(width, height);
}




FluidClass::~FluidClass(){
}




void FluidClass::fluidUpdate(int w, int h){


    
    fluid.allocate(w, h, 0.5);
    ofSetWindowShape(w, h);

    
    // Adding temporal Force
    //
    ofPoint m = ofPoint(ofRandom(500),ofRandom(500));
    ofPoint d = (m - oldM)*10.0;
    oldM = m;
    ofPoint c = ofPoint(640*0.5, 480*0.5) - m;
    c.normalize();
    fluid.addTemporalForce(m, d, ofFloatColor(c.x,c.y,0.5)*sin(ofGetElapsedTimef()),3.0f);


    ofEnableBlendMode(OF_BLENDMODE_ADD);
    fluid.update();
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));



}



 
 void FluidClass::fluidDraw(){
// ofBackgroundGradient(ofColor::gray, ofColor::black, OF_GRADIENT_LINEAR);
 
 fluid.draw();
 }


 //--------------------------------------------------------------
 void FluidClass::keyPressed(int key){
 if( key == 'p')
 bPaint = !bPaint;
 if( key == 'o')
 bObstacle = !bObstacle;
 if( key == 'b')
 bBounding = !bBounding;
 if( key == 'c')
 bClear = !bClear;
 }
 
 //--------------------------------------------------------------
 void FluidClass::keyReleased(int key){
 
 }
 
 //--------------------------------------------------------------
 void FluidClass::mouseMoved(int x, int y ){
 
 }
 
 //--------------------------------------------------------------
 void FluidClass::mouseDragged(int x, int y, int button){
 
 }
 
 //--------------------------------------------------------------
 void FluidClass::mousePressed(int x, int y, int button){
 
 }
 
 //--------------------------------------------------------------
 void FluidClass::mouseReleased(int x, int y, int button){
 
 }
 
 //--------------------------------------------------------------
 void FluidClass::windowResized(int w, int h){
 
 }
 
 //--------------------------------------------------------------
 void FluidClass::gotMessage(ofMessage msg){
 
 }
 
 //--------------------------------------------------------------
 void FluidClass::dragEvent(ofDragInfo dragInfo){
 
 }

