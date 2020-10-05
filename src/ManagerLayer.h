#pragma once

#include "ofxLayerManager.h"
#include "ofxGui.h"
#include "VjObject.h"
#include "ofxXmlSettings.h"

class ManagerLayer 
{
public:
	static int globalMngLayCont;

	ManagerLayer() {};
	~ManagerLayer() {};

	void setup();
	void update();
	void draw();

	void setupLayerByConfig(ofxXmlSettings layersettings);
	void setupAllLayers();
	ofFbo& getFrameBuffer() { return mng.getFramebuffer(); }
	template <typename T > T* createLayer(float defalut_alpha = 0);

	ofParameterGroup fader;
	ofParameterGroup config;
	ofParameterGroup all;

	ofParameterGroup paraRouter;
	ofParameter<int> routTo;


private:

	ofxLayer::Manager mng;

	size_t counter = 0;
	vector<ofxLayer::Layer*> textures;
	vector<ofParameterGroup> configs;
	vector<ofParameter<float>> alphafader;

};


