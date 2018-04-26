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



class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

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
		/*
		CircleGrow * layer1;
		ParticleGrowTexture * layer2;
		ParticleSystemTexture * layer3;
		StripeSpiral * layer4;
		SphereGrow * layer5; 
		StripeCubes * layer6;
		WaveMeshTexture *layer7;
		WaveMeshAdvTex * layer8;
		
		vector<ofxLayer::Layer*> layers;
		vector<VjObject*> layerConfigs;

		vector<ofxButton*> buttons;
		vector<ofxPanel*> guis;
		*/
		//ofxPanel * currentConfig = nullptr;

		ofParameterGroup allGroup;

		ofxOscParameterSync sync;
		
		SoundAnalyzer sound;

		//ofxLayer::Manager mng;

		bool fullscreen = false;

		ManagerLayer mgl;

		void buttonPressed(const void * sender);
		float rms = 0;
};
