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


using namespace ofxLayer;

class SpectrumVisu :
	public ofxLayer::Layer, public VjObject
{
public:

	OFX_LAYER_DEFINE_LAYER_CLASS(SpectrumVisu);

	SpectrumVisu();
	~SpectrumVisu() {};

	virtual void setup() override;
	virtual void update() override;
	virtual void draw() override;

};