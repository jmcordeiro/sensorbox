//
//  background.cpp
//  fish-cv_sensor_box
//
//  Created by Joao Cordeiro on 12/06/15.
//
//

#include "background.h"


background::background(){

    backgroundImg.initGrabber(800, 600);
    backgroundImg.setDeviceID(1);
    imgTotalColor.allocate(800, 600);
    imgTotal.allocate(backgroundImg.width, backgroundImg.height);
    imgRepeat.allocate(backgroundImg.width, backgroundImg.height);

    bNewFrame = true;
}


background::~background(){
    
}


void background::formBackground(){

    //imgTotal.setROI(0, 0, 5, 5);
    
 //   imgRepeat.allocate(imgTotal.getROI().width, imgTotal.getROI().height);
 //   imgRepeat.setFromPixels(imgTotal.getRoiPixels(), imgTotal.getROI().width, imgTotal.getROI().height);
//    imgRepeat.setFromPixels(imgTotal.getRoiPixels(), imgTotal.getROI().width*2, imgTotal.getROI().height*2);
//    imgRepeat.setFromPixels(imgTotal.getRoiPixels(), imgTotal.getROI().width*4, imgTotal.getROI().height*3);
    
}


void background::updateBackground(){

backgroundImg.update();
bNewFrame = backgroundImg.isFrameNew();


    if (bNewFrame){
        imgTotalColor.setFromPixels(backgroundImg.getPixels(), backgroundImg.width, backgroundImg.height);
        imgTotal.setFromColorImage(imgTotalColor);
        cout << backgroundImg.width << " -- " << backgroundImg.height << endl;

    }
    

}


void background::drawBackground(){

 //   imgTotal.drawROI(0, 0);

  //  ofSetHexColor(0xffffff);
  //  imgTotal.draw(0, 0, 800, 600);

    imgTotalColor.draw(0, 0, 800, 600);
    
}