#pragma once
#include "ofMain.h"
#include "ofxLayer.h"
#include "ofxXmlSettings.h"
#include <vector>


struct PreviewConfig
{
	int offsetX;
	int offsetY;
	int width;
	int height;

};

class PreviewApp : public ofBaseApp
{
	std::vector<ofFbo> layers;
	std::vector<PreviewConfig> configs;
	ofxXmlSettings settings;

public:
	void setup() override;
	void update() override;
	void draw() override;
	void exit() override;
	void addLayer(ofFbo lay, PreviewConfig conf);

};

