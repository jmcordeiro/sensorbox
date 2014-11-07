/*
 notes:
 - i'm testing doing the cv with a smaller image and drawing the image from VideGrabber
 - It works not so good and I'm not sure if it computationally less demanding (cpu 74%, memory 98%).
 */


#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // Define the capture size of the c‰mera
    camWidth = 1280;
    camHeight = 720;
    
    
    // ********* FOR PARTICLES *****************
    
    int num = 15;
    p.assign(num, demoParticle(fishPosBig));
    currentMode = PARTICLE_MODE_ATTRACT;
    currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse";
    resetParticles();
    
    
    
    
    // ********* define an initial ROI - Region Of Interest *********
    ROI.width = 1265; // set it to camWidth to have ROI = to camera size
    ROI.height = 390;// set it to camHeight to have ROI = to camera size
    ROI.x = 10; // set it to zero to get ROI = camwidth
    ROI.y = 330; // set it to zero to get ROI = camheight
    
    paralax_x = (camWidth-ROI.width)*0.5;
    paralax_y = (camHeight-ROI.height)*0.5;
    
    // Define a scale ratio to resize the original image for analysis
    scaleRatio = 4;
    
    
#ifdef _USE_LIVE_VIDEO
    // Get back a list of devices (cameras).
    vector<ofVideoDevice> devices = vidGrabber.listDevices();
    
    for(int i = 0; i < devices.size(); i++){
        cout << devices[i].id << ": " << devices[i].deviceName;
        if( devices[i].bAvailable ){
            cout << endl;
        }else{
            cout << " - unavailable " << endl;
        }
    }
    // use camera 0 for the analysis
    vidGrabber.setDeviceID(0);
    
    //vidGrabber.setVerbose(true);  // check what this is!
    vidGrabber.initGrabber(camWidth,camHeight);
#else
    vidPlayer.loadMovie("test_animation.mov");
    vidPlayer.play();
#endif
    
    // **** allocate memory for different images used along the way
    colorImg.allocate(camWidth, camHeight);
    grayTempImage.allocate(camWidth, camHeight);
    grayBg.allocate(ROI.width/scaleRatio, ROI.height/scaleRatio);
    
    
    //******** Selects the method for learning background ***********
    bLearnBakground = false; // learn from video ('space bar')
    bLoadPictureBakground = true; // load from picture file ('p' key)
    
    
    //******** threshold used for image analysis
    threshold = 50;
    
    
    // ************ LINE DECLARATION ********
    firstLine.setCamSize(ROI.width, camHeight, paralax_x, paralax_y);
    //   secondLine.setCamSize(ROI.width, camHeight, paralax_x, paralax_y);
    
    firstLine.setStatus(true);
    firstLine.setThickness(5);
    
    //   secondLine.setStatus(true);
    //   secondLine.setThickness(5);
    
    
    ofSetFrameRate(15);
    
    
    
}



//--------------------------------------------------------------
void ofApp::update(){
    
    ofBackground(0,0,0);
    bool bNewFrame = false;
    
    paralax_x = (camWidth-ROI.width)*0.5;
    paralax_y = (camHeight-ROI.height)*0.5;
    
    
    
    // ************ LINE UPDATE *********
    firstLine.setCamSize(ROI.width, ROI.height, paralax_x, paralax_y);
    //    secondLine.setCamSize(ROI.width, ROI.height, paralax_x, paralax_y);
    
    
#ifdef _USE_LIVE_VIDEO
    vidGrabber.update();
    bNewFrame = vidGrabber.isFrameNew();
#else
    vidPlayer.update();
    bNewFrame = vidPlayer.isFrameNew();
#endif
    
    
    // Assigns a frame from the video/camera to a color image
    if (bNewFrame){
#ifdef _USE_LIVE_VIDEO
        colorImg.setFromPixels(vidGrabber.getPixels(), camWidth, camHeight);
        
#else
        colorImg.setFromPixels(vidPlayer.getPixels(), camWidth, camHeight);
#endif
        
        grayTempImage.clear();
        grayTempImage.allocate(camWidth, camHeight);
        grayTempImage = colorImg;
        grayTempImage.setROI(ROI);
        
        grayImage.clear();
        grayImage.allocate(ROI.width, ROI.height);
        grayImage.setFromPixels(grayTempImage.getRoiPixels(), ROI.width, ROI.height);
        grayImage.resize(ROI.width/scaleRatio, ROI.height/scaleRatio);
        
        
        //******** LEARN BACKGROUND (space bar) *******************
        if (bLearnBakground == true){
            grayBg.clear();
            grayBg.allocate(ROI.width/scaleRatio, ROI.height/scaleRatio);
            grayImage.scaleIntoMe(grayBg);
            grayBg = grayImage;
            
            bgImg.allocate(ROI.width/scaleRatio, ROI.height/scaleRatio, OF_IMAGE_GRAYSCALE);
            unsigned char * pixels = grayBg.getPixels();
            bgImg.setFromPixels(pixels, ROI.width/scaleRatio, ROI.height/scaleRatio, OF_IMAGE_GRAYSCALE);
            bgImg.saveImage("background-"+ofGetTimestampString()+".png");
            
            bLearnBakground = false;
            cout << "------------------" << endl;
            cout << "------------------" << endl;
            cout << "CAPTURE BACKGROUNG" << endl;
            cout << "------------------" << endl;
            cout << "------------------" << endl;
            
        }
        
        
        //******** LOAD BACKGROUND PICTURE ('p' key) *******************
        if (bLoadPictureBakground == true){
            loader.loadImage("background.png");
            cout << "load image from file" << endl;
            loader.setImageType(OF_IMAGE_GRAYSCALE);
            loader.resize(ROI.width/scaleRatio, ROI.width/scaleRatio);
            cout << "resize image" << endl;
            grayBg.clear();
            grayBg.allocate(ROI.width/scaleRatio, ROI.height/scaleRatio);
            grayBg.setFromPixels(loader.getPixels(),ROI.width/scaleRatio, ROI.height/scaleRatio);
            bLoadPictureBakground = false;
        }
        
        
        // take the abs value of the difference between background and incoming and then threshold:
        grayDiff.clear();
        grayDiff.allocate(ROI.width/scaleRatio, ROI.height/scaleRatio);
        grayDiff.absDiff(grayBg, grayImage);
        grayDiff.threshold(threshold);
        
        // **** find contours *******
        contourFinder.findContours(grayDiff, 1, (ROI.width/scaleRatio*ROI.height/scaleRatio/4), 1, false);
        
    }
    
    if (contourFinder.nBlobs > 0){
        fishPosSmall = ofVec2f(contourFinder.blobs[0].centroid.x, contourFinder.blobs[0].centroid.y);
        fishPosBig = ofVec2f(fishPosSmall.x*scaleRatio+(paralax_x), fishPosSmall.y*scaleRatio+(paralax_y));
    }
    
    // this method sends information for fish class variables
    myFish.makeFishToWork(camWidth, camHeight, fishPosBig.x, fishPosBig.y, ROI.width, ROI.height, paralax_x, paralax_y, 100);
    
    
    /*
     cout << "velocity: " << myFish.getVelocity(fishPosBig.x,fishPosBig.y) << endl;
     */
    
    
    
    // *********  FOR PARTICLES ***************
    for(unsigned int i = 0; i < p.size(); i++){
        p[i].setFishPosPrt(fishPosBig);
        p[i].setMode(currentMode);
        p[i].update();
    }
    
    //lets add a bit of movement to the attract points
    for(unsigned int i = 0; i < attractPointsWithMovement.size(); i++){
        attractPointsWithMovement[i].x = attractPoints[i].x + ofSignedNoise(i * 10, ofGetElapsedTimef() * 0.7) * 12.0;
        attractPointsWithMovement[i].y = attractPoints[i].y + ofSignedNoise(i * -10, ofGetElapsedTimef() * 0.7) * 12.0;
    }
    
    
    
}










//--------------------------------------------------------------
void ofApp::draw(){
    
    
    // draw the incoming, the grayscale, the bg and the thresholded difference
    ofSetHexColor(0xffffff);
    
    //vidGrabber.draw(0, 0);
    colorImg.draw((paralax_x)-ROI.x, (paralax_y)-ROI.y);
    
    firstLine.drawLine();
    // secondLine.drawLine();
    
    
    // draws the flickering effect assigned to the rithmic drone. The final argument changes the intensity
    flickering(paralax_x, paralax_y, ROI.width, ROI.height,  40);
    
    
    
    
    if (showCalibrationScreen) {
        
        // *** draw graySmall Image use (ROI scaled) ***
        ofSetHexColor(0xffffff);
        grayImage.draw(0, 0);
        ofNoFill();
        ofSetColor(255, 0, 0);
        ofRect(paralax_x, paralax_y, ROI.width, ROI.height);
        
        // *** draw background image in use ***
        ofSetHexColor(0xffffff);
        grayBg.draw(camWidth/scaleRatio, 0);
        
        
        if (contourFinder.nBlobs > 0){
            
            // *** draw point and contour on small image ***
            ofSetColor(0, 255, 0);
            ofFill();
            ofCircle(contourFinder.blobs[0].centroid.x, contourFinder.blobs[0].centroid.y, 10);
            contourFinder.blobs[0].draw(0, 0);
            
            // *** draw point on big image ***
            ofSetColor(255, 0, 0);
            ofCircle(fishPosBig.x, fishPosBig.y, 10);
            
        }
        
        
        // ****** A report **********************
        ofSetHexColor(0xffffff);
        stringstream reportStr;
        reportStr << "bg subtraction and blob detection" << endl
        << "press ' ' to capture bg" << endl
        << "threshold " << threshold << " (press: +/-)" << endl << "num blobs found " << contourFinder.nBlobs << ", fps: " << ofGetFrameRate() <<endl  << "'p': // loads the picture as learning background" << "'y':  threshold ++ " << "'r': threshold --;" << "'o': ROI width  +;" << "'l': ROI width - ; " << endl <<"'i': ROI height +" <<       " 'k': ROI height - " << "'w': ROI y -" << "'s': ROI y + "<< "'a': ROI x -" << " 'd': ROI x + " << "'z': showCalibrationScreen " << "'q':";
        
        ofDrawBitmapString(reportStr.str(), 20, 600);
        ofDrawBitmapString(ofToString(ofGetFrameRate()), 10, 10);
        // **************************************
        
        
    }else{
        
        // *** draw point on big image *** (comment on real use)
        if (contourFinder.nBlobs > 0){
            ofSetColor(0, 255, 0);
            ofFill();
            ofCircle(fishPosBig.x,fishPosBig.y, 5);
            
        }
        
        // *** draw black frame arround display window ***
        ofSetColor(0, 0, 0);
        ofFill();
        ofRect(0, 0, camWidth, paralax_y);
        ofRect(0, (paralax_y)+ROI.height, camWidth, camHeight);
        ofRect(0, 0, paralax_x, camHeight);
        ofRect((paralax_x)+ROI.width, 0, camWidth, camHeight);
    }
    
    
    
    // ************************ draw Particles ******************
    for(unsigned int i = 0; i < p.size(); i++){
        p[i].draw();
    }
    
    ofSetColor(190);
    if( currentMode == PARTICLE_MODE_NEAREST_POINTS ){
        for(unsigned int i = 0; i < attractPoints.size(); i++){
            ofNoFill();
            ofCircle(attractPointsWithMovement[i], 10);
            ofFill();
            ofCircle(attractPointsWithMovement[i], 4);
        }
    }
    
    ofSetColor(230);
    ofDrawBitmapString(currentModeStr + "\n\nSpacebar to reset. \nKeys 1-4 to change mode.", 10, 20);
    
}






//--------------------------------------------------------------
void ofApp::resetParticles(){

       
        //these are the attraction points used in the forth demo
        attractPoints.clear();
        for(int i = 0; i < 4; i++){
            attractPoints.push_back( ofPoint( ofMap(i, 0, 4, 100, ofGetWidth()-100) , ofRandom(100, ofGetHeight()-100) ) );
        }
        
        attractPointsWithMovement = attractPoints;
        
        for(unsigned int i = 0; i < p.size(); i++){
            p[i].setMode(currentMode);
            p[i].setAttractPoints(&attractPointsWithMovement);;
            p[i].reset();
            

}


}








//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    // ************** For Particles *****************
    if( key == '1'){
        currentMode = PARTICLE_MODE_ATTRACT;
        currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse";
    }
    if( key == '2'){
        currentMode = PARTICLE_MODE_REPEL;
        currentModeStr = "2 - PARTICLE_MODE_REPEL: repels from mouse";
    }
    if( key == '3'){
        currentMode = PARTICLE_MODE_NEAREST_POINTS;
        currentModeStr = "3 - PARTICLE_MODE_NEAREST_POINTS: hold 'f' to disable force";
    }
    if( key == '4'){
        currentMode = PARTICLE_MODE_NOISE;
        currentModeStr = "4 - PARTICLE_MODE_NOISE: snow particle simulation";
        resetParticles();
    }
    
    if( key == ' ' ){
        resetParticles();
    }
    
    
    
    
    // ************** For fish tracking *****************
    
    switch (key) {
            
        case ' ': // loads the picture as learning background
            bLearnBakground = true;
            break;
            
        case 'p': // loads the picture as learning background
            bLoadPictureBakground = true;
            break;
        case 'y':
            threshold ++;
            if (threshold > 255) threshold = 255;
            break;
        case 'r':
            threshold --;
            if (threshold < 0) threshold = 0;
            break;
        case 'o':
            ROI.width = ROI.width+5;
            break;
        case 'l':
            ROI.width = ROI.width-5;
            break;
        case 'i':
            ROI.height = ROI.height+5;
            break;
        case 'k':
            ROI.height = ROI.height-5;
            break;
            
        case 'w':
            ROI.y = ROI.y-5;
            break;
        case 's':
            ROI.y = ROI.y+5;
            break;
        case 'a':
            ROI.x = ROI.x-5;
            break;
        case 'd':
            ROI.x = ROI.x+5;
            break;
        case 'z':
            showCalibrationScreen = !showCalibrationScreen;
            break;
        case 'q':
            cout <<"***************" << endl;
            cout << "GRAY BG: " << grayBg.width << " x " << grayBg.height << endl;
            cout << "GRAY IMG: " << grayImage.width << " x " << grayImage.height << endl;
            cout << "COLOR IMG: " << colorImg.width << " x " << colorImg.height << endl;
            cout << "GRAY TEMP: " << grayTempImage.width << " x " << grayTempImage.height << endl;
            cout << "ROI TEMP: " << grayTempImage.getROI().width << " x " << grayTempImage.getROI().height << endl;
            cout << "ROI x, y: " << grayTempImage.getROI().x << " , " << grayTempImage.getROI().y << endl << endl;
            break;
    }
}


//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
    firstLine.setVelocity(x / 100);
    //secondLine.setVelocity(y / 100);
    
}
