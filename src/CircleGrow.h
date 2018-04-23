#pragma once
#include "ofxLayer.h"
#include "VjObject.h"


using namespace ofxLayer;

class CircleGrow : public ofxLayer::Layer, public VjObject
{
public:

	OFX_LAYER_DEFINE_LAYER_CLASS(CircleGrow);

	CircleGrow();
	~CircleGrow();

	virtual void setup() override;
	virtual void updateEvery() override {}
	virtual void update() override;
	virtual void draw() override;


private:
	float lasttime = 0;
	float time = 0;
	float timerot = 0;
	void setupPoints();

	float edge(float in);

	//ofFbo fbo;
	ofShader shader;

	vector <ofPoint> points;

	ofParameter<float> bogen = 50.0f;
	ofParameter<float> grow = 0.2f;
	ofParameter<float> rotate = 50.0f;
	ofParameter<float> size = 400.0f;
	ofParameter<float> res = 50;
	ofParameter<float> thick = 7.0f;
	ofParameter<ofColor> color;


};

