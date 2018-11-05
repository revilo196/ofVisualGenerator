#pragma once
#include "ofxLayer.h"
#include "VjObject.h"


using namespace ofxLayer;


class StripeSpiral :
	public ofxLayer::Layer, public VjObject
{
public:

	OFX_LAYER_DEFINE_LAYER_CLASS(StripeSpiral);


	StripeSpiral();
	~StripeSpiral();

	virtual void setup() override;
	virtual void update() override;
	virtual void draw()  override;


private:
	float time = 0;
	float lasttime = 0;

	void render();
	//ofFbo fbo;
	ofShader shader;
	ofPlanePrimitive plane;
	
	ofParameter<float> speed;
	ofParameter<float> edges;
	ofParameter<float> circles;
	ofParameter<float> distance;
	ofParameter<float> thik = 0.3;
	ofParameter<float> stripPhaseSpeed;
	ofParameter<float> stripCount;
	ofParameter<float> stripTilt;
	ofParameter<float> stripRot;


};	


