#pragma once
/**
 * @file PreviewApp.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-06-26
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "ofMain.h"
#include "ofxLayer.h"
#include "ofxXmlSettings.h"
#include <vector>

/**
 * @brief Structure for position and size of a preview
 */
struct PreviewConfig
{
	int offsetX;
	int offsetY;
	int width;
	int height;

};

/**
 * @brief Application Window for previewing the Visual Layers
 * 
 */
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

