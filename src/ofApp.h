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
#include "ofxXmlSettings.h"
#include "ofxNDI.h"
#include "MainMixer.h"

//#define SONGBEAMER
//#define SOUND
//#define NDI_OUT
//#define ARTNET_IN


#ifdef SONGBEAMER
	#include "SongBeamer.h"
#endif

#ifdef SOUND
	#include "SoundAnalyzer.h"
#endif

#ifdef NDI_OUT
	#include "ofxNDI.h"
#endif

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void exit();

		
		void drawPreviewLayer(ofxLayer::Layer * layer);
		void updatePre();
		void drawPre(ofEventArgs & args);

		void keyPressed(int key);
		void keyReleased(int key);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofxPanel gui;
		ofxPanel gui2;


		ofParameterGroup allGroup;
		ofxOscParameterSync sync;
		ofxXmlSettings settings;
		

		bool fullscreen = false;

		ManagerLayer  mgl1;
		ManagerLayer  mgl2;
		ManagerLayer  mgl3;
		ManagerLayer  mgl4;

		MainMixer a12;
		MainMixer b34;
		MainMixer outAB;

		ofFbo effectLayer;
		ofFbo preFbo;
		ofFbo preFboOut;
		

		ofPlanePrimitive fullQuad;

		
		#ifdef ARTNET_IN
			int artnet = 0;
			void art();
			ofParameter<float> dimm;
			ofParameter<float> stro;
			ofParameter<float> colR;
			ofParameter<float> colG;
			ofParameter<float> colB;
			ofParameter<bool> artL1;
			ofParameter<bool> artL2;
			ofParameter<bool> artL3;
			ofParameter<bool> artL4;
		#endif // ARTNET_IN


		#ifdef NDI_OUT
			ofxNDIsender ndiSender;    // NDI sender
			char senderName[256];      // Sender name
			ofFbo ndiFbo;
		#endif

		#ifdef SOUND
			float rms = 0;
			int soundID = 0;
			SoundAnalyzer sound;
		#endif

		#ifdef SONGBEAMER
			int videoID = 0;
			SongBeamer sb_mix;
		#endif
};
