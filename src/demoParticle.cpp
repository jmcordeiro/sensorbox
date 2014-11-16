#include "demoParticle.h"

//------------------------------------------------------------------
demoParticle::demoParticle(){
    attractPoints = NULL;
    //   rainIntensity = 1;
}

//------------------------------------------------------------------
demoParticle::demoParticle(int rInt){
    rainIntensity = rInt;
}


//------------------------------------------------------------------
demoParticle::demoParticle(ofVec2f xy){
    fishPosPrt = xy;
    attractPoints = NULL;
}


//------------------------------------------------------------------
void demoParticle::setMode(particleMode newMode){
    mode = newMode;
}

//------------------------------------------------------------------
void demoParticle::setAttractPoints( vector <ofPoint> * attract ){
    attractPoints = attract;
}

//------------------------------------------------------------------
void demoParticle::setFishPosPrt(ofVec2f xy){
    fishPosPrt = xy;
}


//------------------------------------------------------------------
ofVec2f demoParticle::getFishPosPrt(){
    return fishPosPrt;
}

//------------------------------------------------------------------
void demoParticle::reset(){
    
    if( mode == PARTICLE_MODE_NOISE ){
        
        //the unique val allows us to set properties slightly differently for each particle
        uniqueVal = ofRandom(-10000, 10000);
        
        pos.x = fishPosPrt.x;
        pos.y = fishPosPrt.y;
        
        vel.x = ofRandom(-2.0, 2.0);
        vel.y = ofRandom(-3.9);
        
        frc   = ofPoint(0,0,0);
        
        scale = ofRandom(0.5, 1.0);
        
        drag  = ofRandom(0.97, 0.99);
        vel.y = fabs(vel.y) * -6.0; //make the particles all be going up
        
        
    }else if (mode == PARTICLE_MODE_RAIN){
        uniqueVal = ofRandom(-10000, 10000);
        
        pos.x = ofRandom(-100, ofGetWidth());
        pos.y = ofRandom(200,-400);
        
        vel.x = 15;
        vel.y = ofRandom(14, 18);
        
    //    frc   = ofPoint(0,0,0);
        
        scale = 0.5;
        
    //    drag  = ofRandom(0.97, 0.99);
        
    }else{
        
        //the unique val allows us to set properties slightly differently for each particle
        uniqueVal = ofRandom(-10000, 10000);
        
        pos.x = ofRandomWidth();
        pos.y = ofRandomHeight();
        
        vel.x = ofRandom(-3.9, 3.9);
        vel.y = ofRandom(-3.9, 3.9);
        
        frc   = ofPoint(0,0,0);
        
        scale = ofRandom(0.5, 1.0);
        
        
        drag  = ofRandom(0.95, 0.998);
        
    }
}

//------------------------------------------------------------------
void demoParticle::update(){
    
    
    //1 - APPLY THE FORCES BASED ON WHICH MODE WE ARE IN
    
    if( mode == PARTICLE_MODE_ATTRACT ){
        ofPoint attractPt(getFishPosPrt().x, getFishPosPrt().y);
        frc = attractPt-pos; // we get the attraction force/vector by looking at the mouse pos relative to our pos
        frc.normalize(); //by normalizing we disregard how close the particle is to the attraction point
        
        vel *= drag; //apply drag
        vel += frc * 0.6; //apply force
        
        //cout << "fish x: " << getFishPosPrt().x << endl;
        //cout << "fish y: " << getFishPosPrt().y << endl;
        
    }
    else if( mode == PARTICLE_MODE_REPEL ){
        ofPoint attractPt(getFishPosPrt().x, getFishPosPrt().y);
        frc = attractPt-pos;
        
        //let get the distance and only repel points close to the mouse
        float dist = frc.length();
        frc.normalize();
        
        vel *= drag;
        if( dist < 150 ){
            vel += -frc * 0.6; //notice the frc is negative
        }else{
            //if the particles are not close to us, lets add a little bit of random movement using noise. this is where uniqueVal comes in handy.
            frc.x = ofSignedNoise(uniqueVal, pos.y * 0.01, ofGetElapsedTimef()*0.2);
            frc.y = ofSignedNoise(uniqueVal, pos.x * 0.01, ofGetElapsedTimef()*0.2);
            vel += frc * 0.04;
        }
    }else if( mode == PARTICLE_MODE_NOISE ){
        
        float fakeWindX = ofSignedNoise(pos.x * 0.003, pos.y * -0.006, ofGetElapsedTimef() * 0.6);
        
        frc.x = fakeWindX * 0.25 + ofSignedNoise(uniqueVal, pos.y * 0.04) * 0.6;
        frc.y = fabs(ofSignedNoise(uniqueVal, pos.x * 0.006, ofGetElapsedTimef()*0.2) * 0.09 + 0.18)*-1;
        
        vel *= drag;
        vel += frc * 0.9;
        
        //we do this so as to skip the bounds check for the bottom and make the particles go back to the top of the screen
        if( pos.y <= 0 ){
            pos.y = -5;
        }
        
        
        
        /*
         //lets simulate falling snow
         //the fake wind is meant to add a shift to the particles based on where in x they are
         //we add pos.y as an arg so to prevent obvious vertical banding around x values - try removing the pos.y * 0.006 to see the banding
         float fakeWindX = ofSignedNoise(pos.x * 0.003, pos.y * 0.006, ofGetElapsedTimef() * 0.6);
         
         frc.x = fakeWindX * 0.25 + ofSignedNoise(uniqueVal, pos.y * 0.04) * 0.6;
         frc.y = ofSignedNoise(uniqueVal, pos.x * 0.006, ofGetElapsedTimef()*0.2) * 0.09 + 0.18;
         
         vel *= drag;
         vel += frc * 0.4;
         
         //we do this so as to skip the bounds check for the bottom and make the particles go back to the top of the screen
         if( pos.y - vel.y > ofGetHeight() ){
         pos.y -= ofGetHeight();
         }
         */
    } else if( mode == PARTICLE_MODE_NEAREST_POINTS ){
        
        if( attractPoints ){
            
            //1 - find closest attractPoint
            ofPoint closestPt;
            int closest = -1;
            float closestDist = 9999999;
            
            for(unsigned int i = 0; i < attractPoints->size(); i++){
                float lenSq = ( attractPoints->at(i)-pos ).lengthSquared();
                if( lenSq < closestDist ){
                    closestDist = lenSq;
                    closest = i;
                }
            }
            
            //2 - if we have a closest point - lets calcuate the force towards it
            if( closest != -1 ){
                closestPt = attractPoints->at(closest);
                float dist = sqrt(closestDist);
                
                //in this case we don't normalize as we want to have the force proportional to distance
                frc = closestPt - pos;
                
                vel *= drag;
                
                //lets also limit our attraction to a certain distance and don't apply if 'f' key is pressed
                if( dist < 300 && dist > 40 && !ofGetKeyPressed('f') ){
                    vel += frc * 0.003;
                }else{
                    //if the particles are not close to us, lets add a little bit of random movement using noise. this is where uniqueVal comes in handy.
                    frc.x = ofSignedNoise(uniqueVal, pos.y * 0.01, ofGetElapsedTimef()*0.2);
                    frc.y = ofSignedNoise(uniqueVal, pos.x * 0.01, ofGetElapsedTimef()*0.2);
                    vel += frc * 0.4;
                }
            }
        }
        
    }else if( mode == PARTICLE_MODE_RAIN ){
        if( pos.y >= ofGetHeight() ){
            pos.y = -5;
            pos.x = ofRandom(-250, ofGetWidth());
        }
    }
    
    //2 - UPDATE OUR POSITION
    
    pos += vel;
    
}

//------------------------------------------------------------------
void demoParticle::draw(){
    
    if( mode == PARTICLE_MODE_ATTRACT ){
        ofSetColor(0, 0, 0);
        ofLine(pos.x, pos.y, fishPosPrt.x,fishPosPrt.y);
    }
    else if( mode == PARTICLE_MODE_REPEL ){
        ofSetColor(0, 0, 0);
        ofCircle(pos.x, pos.y, scale * 4.0);
    }
    else if( mode == PARTICLE_MODE_NOISE ){
        ofSetColor(0, 0, 0);
        ofCircle(pos.x, pos.y, scale * 4.0);
    }
    else if( mode == PARTICLE_MODE_NEAREST_POINTS ){
        ofSetColor(0, 0, 0);
        ofCircle(pos.x, pos.y, scale * 4.0);
    }
    else if( mode == PARTICLE_MODE_RAIN){
        ofSetColor(0, 0, 0, rainIntensity*2.75-pos.y);
        ofSetLineWidth(scale);
        ofLine(pos.x, pos.y, pos.x-10, pos.y-15);
    }
}

