/*
 notes:
 - i'm testing doing the cv with a smaller image and drawing the image from VideGrabber
 - It works not so good and I'm not sure if it computationally less demanding (cpu 74%, memory 98%).
*/


#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){


    whichBackgroundImg = 1;
    myfont.loadFont("fonts/arial.ttf", 13);
    numOfColls = 2;
    numOfRows = 2;
    isNotMute = false;
    
    toogleSounds = 0;
    
    bLearnBackground = true; //ofxBckgrd
    
    decreases = 0;
    // Define the capture size of the câmera (facetime hd on the mac 1280x720)
    camWidth = 800;
    camHeight = 600;
    
    prtInt = 255;
    
    blackFrame = false;
    
    // ********* define an initial ROI - Region Of Interest *********
    ROI.width = camHeight; // set it to camWidth to have ROI = to camera size
    ROI.height = camHeight;// set it to camHeight to have ROI = to camera size
    ROI.x = (camWidth-camHeight)*0.5; // set it to zero to get ROI = camwidth
    ROI.y = 0; // set it to zero to get ROI = camheight
  
    
    paralax_x = 200;
    paralax_y = 50;
    
    // Define a scale ratio to resize the original image for analysis
    //scaleRatio = 4;
    
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
    vidGrabber.setDeviceID(0);  // use camera 0 for the analysis
    vidGrabber.initGrabber(camWidth,camHeight);
    
#else
    vidPlayer.loadMovie("fish_movie.mov");
    vidPlayer.play();
    vidPlayer.setLoopState(OF_LOOP_NORMAL);
#endif
    
    
    // **** allocate memory for different images used along the way
    myBackgroundAddon.allocate(camWidth,camHeight); //ofxBckgrd


    
    //******** threshold used for image analysis ******************
//    threshold = 50;
    
    ofSetFrameRate(15);
    
    sound_1.loadSound("sounds/sound_1.wav");
    sound_2.loadSound("sounds/sound_2.wav");
    sound_3.loadSound("sounds/sound_3.wav");
    sound_4.loadSound("sounds/sound_4.wav");
    
    sound_1.setLoop(true);
    sound_2.setLoop(true);
    sound_3.setLoop(true);
    sound_4.setLoop(true);
    
}



//--------------------------------------------------------------
void ofApp::update(){
    
    ofSoundUpdate();
    
    if (toogleSounds > 4) {
        toogleSounds = 0;
    }
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    ofBackground(255,255,255);
    bool bNewFrame = false;
    

    
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
        colorImg.setROI(ROI);
        myBackgroundAddon.update(colorImg);

#else
        colorImg.setFromPixels(vidPlayer.getPixels(), camWidth, camHeight);
#endif
        

        
        // **** find contours *******
        
        contourFinder.findContours(myBackgroundAddon.backgroundCodeBookConnectedComponents, 0.01, (ROI.width*ROI.height/8), 1, false);
        //contourFinder.findContours(grayDiff, 0.01, (ROI.width/scaleRatio*ROI.height/scaleRatio/4), 1, false);

    }
    
    
    
    if(bLearnBackground){
        myBackgroundAddon.startLearning();
        bLearnBackground = false;
    }

    
    
    
    if (contourFinder.nBlobs > 0){

        fishPosBig = ofVec2f(contourFinder.blobs[0].centroid.x, contourFinder.blobs[0].centroid.y);

    }
    
    // ******* plays the sounds in "playmode" *********
    if (isNotMute) {
        
        if(contourFinder.nBlobs > 0){
            switch (theCell) {
                case 0:
                    ofSoundStopAll();
                    theCell = 0;
                    break;
                case 1:
                    if (!sound_1.getIsPlaying()) {
                        ofSoundStopAll();
                        sound_1.play();
                    }
                    break;
                case 2:
                    if (!sound_2.getIsPlaying()) {
                        ofSoundStopAll();
                        sound_2.play();
                    }
                    break;
                case 3:
                    if (!sound_3.getIsPlaying()) {
                        ofSoundStopAll();
                        sound_3.play();
                    }
                    break;
                case 4:
                    if (!sound_4.getIsPlaying()) {
                        ofSoundStopAll();
                        sound_4.play();
                    }
                    break;
                default:
                    ofSoundStopAll();
                    theCell = 0;
                    break;
            }
            
        }else{
            ofSoundStopAll();
            theCell = 0;
        }
    }
    
    
    
    // ******* plays the teste sounds by pressing "C" *********
    if (!isNotMute) {
        
        switch (toogleSounds) {
                
            case 1:
                if (!sound_1.getIsPlaying()) {
                    //cout << "1\n";
                    ofSoundStopAll();
                    sound_1.play();
                }
                break;
            case 2:
                if (!sound_2.getIsPlaying()) {
                    ofSoundStopAll();
                    sound_2.play();
                }
                break;
            case 3:
                if (!sound_3.getIsPlaying()) {
                    ofSoundStopAll();
                    sound_3.play();
                }
                break;
            case 4:
                if (!sound_4.getIsPlaying()) {
                    ofSoundStopAll();
                    sound_4.play();
                }
                break;
            case 0:
                ofSoundStopAll();
                break;
            default:
                break;
        }
        
    }
    
    
    
    // this method sends information for fish class variables
    myFish.makeFishToWork(camWidth, camHeight, fishPosBig.x, fishPosBig.y, ROI.width, ROI.height, ROI.x, ROI.y, 100);
    
    // cout << "velocity: " << myFish.getVelocity(fishPosBig.x,fishPosBig.y) << endl;
    
    //update volume values of the GUI
    sound_1.setVolume(myGui.getVol_1());
    sound_2.setVolume(myGui.getVol_2());
    sound_3.setVolume(myGui.getVol_3());
    sound_4.setVolume(myGui.getVol_4());
    
    
    // sets the variable "theCell" with the correspondent quadrant where the fish is positioned
    theCell = myCell(ROI.x, ROI.y, ROI.width, ROI.height, numOfRows, numOfColls, fishPosBig.x, fishPosBig.y);
    
    if (blackFrame){
        
        // makes a full read every 333 miliseconds
        if (ofGetElapsedTimeMillis()%333 < decreases){
            myLogger.listenAndSendOneReading(theCell, myFish.getVelocity(), fishPosBig.x, fishPosBig.y, mySoundInput.getSoundVolume(), myArduino.getTemp(), myArduino.getHum());
            decreases = 0;
        }else{
            decreases = ofGetElapsedTimeMillis()%333;
        }
        
    }
    
    myArduino.readFromArduino();
    
}



//--------------------------------------------------------------
void ofApp::draw(){
    
    
    // draw the incoming, the grayscale, the bg and the thresholded difference
    ofSetHexColor(0xffffff);
    
    
    // *********** draw the video **************************
    colorImg.draw(200,50);
    drawGridCell(ROI.x+200, ROI.y+50, ROI.width, ROI.height, numOfRows, numOfColls);
    
    
    
    //*********** WRITING To FILE MODE (z) *****************
    //********** draw black bars arround display window ***
    
    if (blackFrame) {
        ofSetColor(0, 0, 0);
        ofFill();
        ofRect(0, 0, ofGetWindowWidth(), paralax_y+ROI.y); // barra superior
        ofRect(0, (paralax_y)+ROI.height+ROI.y, ofGetWindowWidth(), ofGetWindowHeight()-((paralax_y)+ROI.height+ROI.y)); // barra inferior
        ofRect(0, 0, paralax_x+ROI.x, ofGetWindowHeight()); // barra esquerda
        ofRect((paralax_x)+ROI.width+ROI.x, 0, ofGetWindowWidth()-((paralax_x)+ROI.width+ROI.x), ofGetWindowHeight()); // barra direita
        ofSetColor(255, 0, 0);
    }
    
    
    // draw grey bars of the sides
    ofSetColor(100);
    ofFill();
    ofRect(0,0, 210,ofGetWindowHeight());
    ofRect(ofGetWindowWidth()-300, 0, 300, ofGetWindowHeight());

    
    // *********** draw sound modes string **************************
    if(blackFrame){
        ofSetColor(255,0,0);
        myfont.drawString("READING TO FILE (z)", ofGetWindowWidth() - (myfont.getNumCharacters()*2.5),40);
    }else{
        ofSetColor(255);
        myfont.drawString("NOT READING TO FILE (z)", ofGetWindowWidth() - (myfont.getNumCharacters()*2.5),40);
    }
    
    
    if (isNotMute){
        ofSetColor(0, 255, 0);
        myfont.drawString("PLAYING MODE (x)", ofGetWindowWidth() - (myfont.getNumCharacters()*2.5),70);
    }else{
        ofSetColor(255, 0, 0);
        myfont.drawString("SILENT MODE (x)", ofGetWindowWidth() - (myfont.getNumCharacters()*2.5),70);
        if (toogleSounds != 0) {
            myfont.drawString("TESTING SOUND "+ofToString(toogleSounds) + " (c)", ofGetWindowWidth() - (myfont.getNumCharacters()*2.5),100);
        }else{
            ofSetColor(255, 255, 255);
            myfont.drawString("NO TEST SOUND (c)", ofGetWindowWidth() - (myfont.getNumCharacters()*2.5),100);
        }
    }
    
    
    ofSetColor(255, 255, 255);
    myfont.drawString("Temperature: " + ofToString(myArduino.getTemp()), ofGetWindowWidth() - (myfont.getNumCharacters()*2.5),140);
    
    ofSetColor(255, 255, 255);
    myfont.drawString("Humidity: " + ofToString(myArduino.getHum()), ofGetWindowWidth() - (myfont.getNumCharacters()*2.5),165);
    
    ofSetColor(255, 255, 255);
    myfont.drawString("Cell: " + ofToString(theCell), ofGetWindowWidth() - (myfont.getNumCharacters()*2.5),190);
    
    ofSetColor(255, 255, 255);
    myfont.drawString("Volume: " + ofToString(roundf(mySoundInput.getSoundVolume())), ofGetWindowWidth() - (myfont.getNumCharacters()*2.5),215);
    
    
    ofSetColor(255, 0, 0);
    ofFill();
    switch (whichBackgroundImg) {
        case 1:
            ofRectangle(10, grayBg.getHeight()*2, bgImgNightStatic.width*0.5, bgImgNightStatic.height*0.5);
            break;
        case 2:
            ofRectangle(10+bgImgDayStatic.width*0.5, grayBg.getHeight()*2, bgImgDayStatic.width*0.5, bgImgDayStatic.height*0.5);
            break;
        case 3:
            ofRectangle(10,grayBg.getHeight()*2+bgImgDay.height*0.5, bgImgDay.width*0.5, bgImgDay.height*0.5);
            break;
        case 4:
            ofRectangle(10+bgImgNight.width*0.5, grayBg.getHeight()*2+bgImgNight.height*0.5, bgImgNight.width*0.5, bgImgNight.height*0.5);
            break;
            
        default:
            break;
    }

    
    if (contourFinder.nBlobs > 0){
        // *** draw green point and contour on big image ***
        ofSetColor(0, 255, 0);
        ofFill();
        ofCircle(contourFinder.blobs[0].centroid.x+(paralax_x), contourFinder.blobs[0].centroid.y+paralax_y, 10);
        contourFinder.blobs[0].draw(paralax_x, paralax_y);
        
        myCellDraw(theCell,ROI.width, ROI.height, numOfRows, numOfColls, paralax_x, paralax_y, ROI.x, ROI.y);
        
    }
    
    ofSetColor(255, 0, 0);
    ofNoFill();
    ofSetLineWidth(4);

    
    //Draws the audio GUI
    myGui.drawGui(ofGetWindowWidth() - 240, ofGetWindowHeight()-150);
    
    myBackgroundAddon.draw(0,0, 10, 10);
    
    
}






//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    keyDown[key] = false;
    
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    keyDown[key] = true;
    
    
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
            blackFrame = !blackFrame;
            break;
        case 'x':
            isNotMute = !isNotMute;
            break;
        case 'c':
            toogleSounds++;
            break;
        case '0':
            numOfRows--;
            break;
        case '9':
            numOfRows++;
            break;
        case '7':
            numOfColls--;
            break;
        case '8':
            numOfColls++;
            break;
        case 'j':
            bLearnBackground = true;
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
}



//--------------------------------------------------------------
void ofApp::exit() {
}




