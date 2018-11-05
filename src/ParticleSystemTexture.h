#pragma once
#include "ofxLayer.h"
#include "VjObject.h"
#include "ParticleSystem.h"

using namespace ofxLayer;

class ParticleSystemTexture : public ofxLayer::Layer, public VjObject
{
public:

	OFX_LAYER_DEFINE_LAYER_CLASS(ParticleSystemTexture);

	ParticleSystemTexture();
	~ParticleSystemTexture();

	virtual void setup() override;
	virtual void update() override;
	virtual void draw()  override;

private:
	ParticleSystem * system;


	ofParameter<float> speed;
	ofParameter<float> forceAmplitude;
	ofParameter<float> scale;
	ofParameter<float> partVel;

	ofParameter<float>rgb_r;
	ofParameter<float>rgb_g;

	ofParameter<float>rgb_b;


	ofFloatColor colorParm;
};

