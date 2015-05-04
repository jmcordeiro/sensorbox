/*
 notes:
 - i'm testing doing the cv with a smaller image and drawing the image from VideGrabber
 - It works not so good and I'm not sure if it computationally less demanding (cpu 74%, memory 98%).
 */


#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    myfont.loadFont("fonts/arial.ttf", 15);
    
    isNotMute = false;
    
    toogleSounds = 0;
    
    decreases = 0;
    // Define the capture size of the câmera (facetime hd on the mac 1280x720)
    camWidth = 1280;
    camHeight = 720;
    
    prtInt = 255;
    
    blackFrame = false;
    
    // ********* define an initial ROI - Region Of Interest *********
    ROI.width = camHeight; // set it to camWidth to have ROI = to camera size
    ROI.height = camHeight;// set it to camHeight to have ROI = to camera size
    ROI.x = (camWidth-camHeight)*0.5; // set it to zero to get ROI = camwidth
    ROI.y = 0; // set it to zero to get ROI = camheight
    
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
    vidGrabber.setDeviceID(0);  // use camera 0 for the analysis
    
    vidGrabber.initGrabber(camWidth,camHeight);
#else
    vidPlayer.loadMovie("fish_movie.mov");
    vidPlayer.play();
    vidPlayer.setLoopState(OF_LOOP_NORMAL);
#endif
    
    // **** allocate memory for different images used along the way
    colorImg.allocate(camWidth, camHeight);
    grayTempImage.allocate(camWidth, camHeight);
    grayBg.allocate(ROI.width/scaleRatio, ROI.height/scaleRatio);
    bgImgNight.allocate(ROI.width/scaleRatio, ROI.height/scaleRatio, OF_IMAGE_GRAYSCALE);
    bgImgDay.allocate(ROI.width/scaleRatio, ROI.height/scaleRatio, OF_IMAGE_GRAYSCALE);
    grayImage.allocate(ROI.width, ROI.height);
    grayDiff.allocate(ROI.width/scaleRatio, ROI.height/scaleRatio);

    
    
//    //******** Selects the method for learning background ***********
//    bLearnBakground = false; // learn from video ('space bar')
//    bLoadPictureBakground = true; // load from picture file ('p' key)

    
    // loads a default background image;
    loader.loadImage("backgrounds/background_black.png");
    loader.setImageType(OF_IMAGE_GRAYSCALE);
    loader.resize(ROI.width/scaleRatio, ROI.width/scaleRatio);
    grayBg.clear();
    grayBg.allocate(ROI.width/scaleRatio, ROI.height/scaleRatio);
    grayBg.setFromPixels(loader.getPixels(),ROI.width/scaleRatio, ROI.height/scaleRatio);
    
    
    bgImgDay.loadImage("backgrounds/background_day.png");
    bgImgNight.loadImage("backgrounds/background_night.png");
    
    //******** threshold used for image analysis ******************
    threshold = 50;
    
    
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
    
    paralax_x = (camWidth-ROI.width)*0.5;
    paralax_y = (camHeight-ROI.height)*0.5;
    
    
    
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
        
        
        //******** LEARN BACKGROUND *******************
        //********** DAY MODE (space bar + 1) ***************
        if (keyDown['1'] && keyDown[' ']) {
            grayBg.clear();
            grayBg.allocate(ROI.width/scaleRatio, ROI.height/scaleRatio);
            grayImage.scaleIntoMe(grayBg);
            grayBg = grayImage;
            
            bgImgDay.allocate(ROI.width/scaleRatio, ROI.height/scaleRatio, OF_IMAGE_GRAYSCALE);
            unsigned char * pixels = grayBg.getPixels();
            bgImgDay.setFromPixels(pixels, ROI.width/scaleRatio, ROI.height/scaleRatio, OF_IMAGE_GRAYSCALE);
            bgImgDay.saveImage("background_day.png");
        }
        
        //********** NIGHT MODE (space bar + 2) ***************
        if (keyDown['2'] && keyDown[' ']) {
            grayBg.clear();
            grayBg.allocate(ROI.width/scaleRatio, ROI.height/scaleRatio);
            grayImage.scaleIntoMe(grayBg);
            grayBg = grayImage;
            
            bgImgNight.allocate(ROI.width/scaleRatio, ROI.height/scaleRatio, OF_IMAGE_GRAYSCALE);
            unsigned char * pixels = grayBg.getPixels();
            bgImgNight.setFromPixels(pixels, ROI.width/scaleRatio, ROI.height/scaleRatio, OF_IMAGE_GRAYSCALE);
            bgImgNight.saveImage("background_night.png");
        }
        
        
        //******** LOAD BACKGROUND PICTURE *******************
        //******* Day Barcground '1' key *************
        if (keyDown['1'] && keyDown['p']) {
            loader.loadImage("background_day.png");
            loader.setImageType(OF_IMAGE_GRAYSCALE);
            loader.resize(ROI.width/scaleRatio, ROI.width/scaleRatio);
            grayBg.clear();
            grayBg.allocate(ROI.width/scaleRatio, ROI.height/scaleRatio);
            grayBg.setFromPixels(loader.getPixels(),ROI.width/scaleRatio, ROI.height/scaleRatio);
        }
        
        //******* Day Barcground '2' key *************
        if (keyDown['2'] && keyDown['p']) {
            loader.loadImage("background_night.png");
            loader.setImageType(OF_IMAGE_GRAYSCALE);
            loader.resize(ROI.width/scaleRatio, ROI.width/scaleRatio);
            grayBg.clear();
            grayBg.allocate(ROI.width/scaleRatio, ROI.height/scaleRatio);
            grayBg.setFromPixels(loader.getPixels(),ROI.width/scaleRatio, ROI.height/scaleRatio);
        }
        
        
        
        
        /* *********** OLD WAY OF DOING IT ************
         
         // ******** LEARN BACKGROUND (space bar) *******************
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
         
         
         
         // ******** LOAD BACKGROUND PICTURE ('p' key) *******************
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
         */
        
        
        
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
    myFish.makeFishToWork(camWidth, camHeight, fishPosBig.x, fishPosBig.y, ROI.width, ROI.height, paralax_x, paralax_y, 100);
    
    // cout << "velocity: " << myFish.getVelocity(fishPosBig.x,fishPosBig.y) << endl;
    
    //update volume values of the GUI
    sound_1.setVolume(myGui.getVol_1());
    sound_2.setVolume(myGui.getVol_2());
    sound_3.setVolume(myGui.getVol_3());
    sound_4.setVolume(myGui.getVol_4());
    
    
    // sets the variable "theCell" with the correspondent quadrant where the fish is positioned
    theCell = myCell(paralax_x, paralax_y, ROI.width, ROI.height, 2, 2, fishPosBig.x, fishPosBig.y);
    
    if (blackFrame){
        
        // makes a full read every 333 miliseconds
        if (ofGetElapsedTimeMillis()%333 < decreases){
            myLogger.listenAndSendOneReading(theCell, myFish.getVelocity(), fishPosBig.x, fishPosBig.y, ofRandom(120), myArduino.getTemp(), myArduino.getHum());
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
    colorImg.draw((paralax_x)-ROI.x, (paralax_y)-ROI.y);
    drawGridCell(paralax_x, paralax_y, ROI.width, ROI.height, 2, 2);
    
    
    //*********** WRITING To FILE MODE (z) *****************
    //********** draw black bars arround display window ***
    
    if (blackFrame) {
        ofSetColor(0, 0, 0);
        ofFill();
        ofRect(0, 0, camWidth, paralax_y);
        ofRect(0, (paralax_y)+ROI.height, camWidth, camHeight);
        ofRect(0, 0, paralax_x, camHeight);
        ofRect((paralax_x)+ROI.width, 0, camWidth, camHeight);
        ofSetColor(255, 0, 0);
        myfont.drawString("READING TO FILE (z)", camWidth - (myfont.getNumCharacters()*2.5),40);
    }
    
    
    // *********** draw sound modes tring **************************
    if (isNotMute){
        ofSetColor(0, 255, 0);
        myfont.drawString("PLAYING MODE (x)", camWidth - (myfont.getNumCharacters()*2.5),70);
    }else{
        ofSetColor(255, 0, 0);
        myfont.drawString("SILENT MODE (x)", camWidth - (myfont.getNumCharacters()*2.5),70);
        if (toogleSounds != 0) {
            myfont.drawString("TESTING SOUND "+ofToString(toogleSounds) + " (c)", camWidth - (myfont.getNumCharacters()*2.5),100);
        }else{
            ofSetColor(255, 255, 255);
            myfont.drawString("NO TESTING SOUND (c)", camWidth - (myfont.getNumCharacters()*2.5),100);
        }
    }
    
    
    // *** draw red rectangle on big image (ROI) ***
    ofNoFill();
    ofSetColor(255, 0, 0);
    ofRect(paralax_x, paralax_y, ROI.width, ROI.height);
    
    // *** draw graySmall Image use (ROI scaled) ***
    ofSetHexColor(0xffffff);
    grayImage.draw(10,0);
    
    // *** draw difference ***
    grayDiff.draw(10, grayBg.getHeight());
    
    // *** draw DAY background image in use ***
    bgImgDay.draw(10, grayBg.getHeight()*2);
    
    // *** draw DAY background image in use ***
    bgImgNight.draw(10, grayBg.getHeight()*3);
    
    
    
    if (contourFinder.nBlobs > 0){
        // *** draw point and contour on small image ***
        ofSetColor(0, 255, 0);
        ofFill();
        ofCircle(10+contourFinder.blobs[0].centroid.x, contourFinder.blobs[0].centroid.y, 10);
        contourFinder.blobs[0].draw(10, 0);
        
        // *** draw point on big image ***
        ofSetColor(255, 0, 0);
        ofCircle(fishPosBig.x, fishPosBig.y, 10);
        
        myCellDraw(paralax_x, paralax_y, ROI.width, ROI.height, 2, 2, fishPosBig.x, fishPosBig.y);
        
    }
    
    myGui.drawGui(camWidth - 230, camHeight-150);
    
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
    
    // clean up
}




