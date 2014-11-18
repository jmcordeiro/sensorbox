#pragma once
#include "ofMain.h"
#include "liveFish.h"

enum particleMode{
	PARTICLE_MODE_ATTRACT = 0,
	PARTICLE_MODE_REPEL,
	PARTICLE_MODE_NEAREST_POINTS,
	PARTICLE_MODE_NOISE,
    PARTICLE_MODE_RAIN
};

class demoParticle{

protected:
    ofVec2f fishPosPrt;
    
	public:
		demoParticle();
        demoParticle(ofVec2f);
        demoParticle(int);

		void setMode(particleMode newMode);
		void setAttractPoints( vector <ofPoint> * attract );

		void reset();
		void update();
		void draw();		
		
		ofPoint pos;
		ofPoint vel;
		ofPoint frc;
		
		float drag; 
		float uniqueVal;
		float scale;
        int rainIntensity;
        int prtIntensity;
    
		particleMode mode;
		
		vector <ofPoint> * attractPoints;
    
        void setFishPosPrt(ofVec2f);
        ofVec2f getFishPosPrt();

    
    
};