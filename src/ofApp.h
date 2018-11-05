#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "CircleGrow.h"
#include "ParticleGrowTexture.h"
#include "ParticleSystemTexture.h"
#include "StripeSpiral.h"
#include "SphereGrow.h"
#include "StripeCubes.h"
#include "WaveMeshTexture.h"
#include "WaveMeshAdvTex.h"

#include "ofxOscParameterSync.h"

#include "ofxLayerManager.h"

#include "ManagerLayer.h"

#include "SoundAnalyzer.h"

#include "MainMixer.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void art();

		void updatePre();
		void drawPre(ofEventArgs & args);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofxPanel gui;
		ofxPanel gui2;


		ofParameterGroup allGroup;
		ofxOscParameterSync sync;

		
		SoundAnalyzer sound;

		bool fullscreen = false;

		ManagerLayer  mgl1;
		ManagerLayer  mgl2;
		ManagerLayer  mgl3;
		ManagerLayer  mgl4;

		MainMixer a12;
		MainMixer b34;

		MainMixer outAB;

		ofFbo preFbo;
		ofFbo preFboOut;

		void songBeamerInputRender();
		ofFbo sbEffectOut;
		ofFbo effectLayer;
		ofFbo songOverlay;
		ofShader yExBlur;
		ofShader xExBlur;
		ofShader sbmix;
		ofShader sbAdd;
		ofFbo xEx;
		ofFbo yEx;
		ofFbo xExB;
		ofFbo yExB;


		ofPlanePrimitive fullQuad;
		
		ofVideoGrabber videoIn;

		ofParameter<bool> fullSong;
		ofParameter<bool> blkSong;
		ofParameter<float> dimm;
		ofParameter<float> stro;
		ofParameter<float> colR;
		ofParameter<float> colG;
		ofParameter<float> colB;
		ofParameter<float> songFade;

		ofParameter<bool> artL1;
		ofParameter<bool> artL2;
		ofParameter<bool> artL3;
		ofParameter<bool> artL4;
		

		//ofxLayer::Manager mainMixer;

		void buttonPressed(const void * sender);
		float rms = 0;
};
