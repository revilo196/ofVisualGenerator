#pragma once
/**
 * @file ofApp.h
 * @author Oliver Walter
 * @brief ofVisualGenerator MainApp header
 * @version 0.1
 * @date 2020-06-26
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "ofMain.h"
#include "ofxGui.h"

#include "ofxOscParameterSync.h"
#include "ofxXmlSettings.h"

#include "MainMixer.h"
#include "ManagerLayer.h"
#include "PreviewApp.h"

/// Enable nedded modules
//#define SONGBEAMER
#define SOUND
#define NDI_OUT
#define ARTNET_IN


#ifdef SONGBEAMER
	#include "SongBeamer.h"
#endif

#ifdef SOUND
	#include "SoundAnalyzer.h"
#endif

#ifdef NDI_OUT
	#include "ofxNDI.h"
#endif

/**
 * @brief ofApp main application window
 */
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void exit();
		void keyPressed(int key);
		void keyReleased(int key);
		void windowResized(int w, int h);


		ofxPanel gui;				//gui for debug and development
		ofParameterGroup allGroup;	//all Parametergroups for the gui
		ofxOscParameterSync sync;	//OscParameter Server

		ofxXmlSettings settings;	//XML settings file
		
		shared_ptr<PreviewApp>  preview; //connection to the preview window app
		bool fullscreen = false; //toggle for fullscreen


		//Effect Layer with multible effects
		ManagerLayer  mgl1;	// Effect layer 1
		ManagerLayer  mgl2; // Effect layer 2
		ManagerLayer  mgl3; // Effect layer 3
		ManagerLayer  mgl4; // Effect layer 4

		//Mixer for the layers
		MainMixer a12;    //Mixer_A:   Mixes layer 1 and layer 2 with possible effects
		MainMixer b34;    //Mixer_B:   Mixes layer 3 and layer 4 with possible effects
		MainMixer outAB;  //Mixer_Out: Mixes the the output of mixer A and mixer B

		// Wrapper of the mixers to render them to an Fbo for Preview
		MixerFboWrapper wa12;   // mixers to Fbo for Preview
		MixerFboWrapper wb34;	// mixers to Fbo for Preview
		MixerFboWrapper effectEndMixer;  // mixers to Fbo for Preview and final output

		/// TODO: Replace with a ofDrawRectangle(...)
		ofPlanePrimitive fullQuad; 

		
		#ifdef ARTNET_IN
		// Artnet Module Parameters
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
		// NDI Module Varables
			ofxNDIsender ndiSender;    // NDI sender
			char senderName[256];      // Sender name
		#endif

		#ifdef SOUND
		// Sound analysing components
			float rms = 0;
			int soundID = 0;
			SoundAnalyzer sound;
		#endif

		#ifdef SONGBEAMER
		// Songbeamer vide input module and overlay 
			int videoID = 0;
			SongBeamer sb_mix;
		#endif
};
