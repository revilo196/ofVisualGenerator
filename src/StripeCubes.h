#pragma once

#include "ofxLayer.h"
#include "VjObject.h"
#include "ofxAnimatableFloat.h"

using namespace ofxLayer;


class StripeCubes :
	 public ofxLayer::Layer, public VjObject
{
public:
	OFX_LAYER_DEFINE_LAYER_CLASS(StripeCubes);

	StripeCubes();
	~StripeCubes();

	virtual void setup() override;
	virtual void update() override;
	virtual void draw() override;
	void setCubes(int count);

private:

	void rotateBoxes();
	void drawBoxes();
	void render();
	float deltatime = 0;
	float lasttime = 0;
	float time = 0;
	float time_stripes = 0;


	ofShader shader;
	//ofFbo fbo;
	vector<ofBoxPrimitive> boxes;
	vector<ofVec3f> rotations;
	vector<float> speeds;
	
	ofParameter<float> speed;
	ofParameter<float> speedStripes;
	ofParameter<float> thikStripes;
	ofParameter<float> tiltStripes;
	ofParameter<float> addSpeed = 0.5;
	ofParameter<bool> out = false;

	ofxAnimatableFloat radius;

};

