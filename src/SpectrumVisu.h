#pragma once
/**
 * @file SpectrumVisu.h
 * @author oliver walter
 * @brief spectrum drawing
 * @version 0.1
 * @date 2020-06-27
 * 
 * @copyright Copyright (c) 2020
 */

#include "ofxLayer.h"
#include "VjObject.h"
#include "ofxShaderFilter.h"


using namespace ofxLayer;

class SpectrumVisu :
	public ofxLayer::Layer, public VjObject
{
	ofxShaderFilter wave;
	ofxShaderFilter blurX;
	ofxShaderFilter blurY;
	//ofFbo pingPong[2];
	ofFbo fbo;
	float runtime;
public:

	OFX_LAYER_DEFINE_LAYER_CLASS(SpectrumVisu);

	SpectrumVisu();
	~SpectrumVisu() {};

	virtual void setup() override;
	virtual void update() override;
	virtual void draw() override;

	ofParameter<float> gain;

	ofParameter<float> speed;
	ofParameter<float> disort;
	ofParameter<float> freq;
	ofParameter<float> blurXval;
	ofParameter<float> blurYval;
	ofParameter<float> minheight;
	ofParameter<float> xoffset;
	

	ofParameter<float> max_rgb_r;
	ofParameter<float> max_rgb_g;
	ofParameter<float> max_rgb_b;

	ofParameter<float> min_rgb_r;
	ofParameter<float> min_rgb_g;
	ofParameter<float> min_rgb_b;
};