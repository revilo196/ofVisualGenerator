#pragma once

#include "ofxLayer.h"
#include "VjObject.h"


using namespace ofxLayer;

class SphereGrow :
	public ofxLayer::Layer, public VjObject
{
public:

	OFX_LAYER_DEFINE_LAYER_CLASS(SphereGrow);


	SphereGrow();
	~SphereGrow();

	virtual void setup() override;
	virtual void update() override;
	virtual void draw() override;


private:

	float edge(float in);

	float lasttime = 0;
	float rmsTime = 0;
	static const size_t sphereCount = 10;
	vector <ofIcoSpherePrimitive> sphere;
	float phase = 0;
	ofParameter<float> grow = 0.3f;
	ofParameter<float> size = 0.1;
	ofShader shader;
	//ofFbo fbo;
};

