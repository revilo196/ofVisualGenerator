#pragma once
#include "VjObject.h"
#include "ofxLayer.h"

using namespace ofxLayer;


class MainMixer: public ofxLayer::Layer
{
public:
	static int globalMainMixCont;


	OFX_LAYER_DEFINE_LAYER_CLASS(MainMixer);

	MainMixer();
	~MainMixer();


	virtual void setup(ofxLayer::Layer * l1, ofxLayer::Layer * l2, int w, int h);
	virtual void update() override;
	virtual void draw() override;

	ofParameterGroup all;

private:
	int width;
	int height;
	virtual void setup() {};
	ofxLayer::Layer * l1;
	ofxLayer::Layer * l2;
	ofPlanePrimitive fullQuad;
	ofShader shader;
	ofShader blurXShader;
	ofShader blurYShader;
	ofFbo fbo_layer1;
	ofFbo fbo_layer2;
	ofFbo fbo_layer1_efx;
	ofFbo fbo_layer2_efx;
	ofParameter<int> mode;
	ofParameter<int> submodeA;
	ofParameter<int> submodeB;
	ofParameter<float> fader;
	ofParameter<int> invertA;
	ofParameter<int> invertB;
	ofParameter<int> efxA;
	ofParameter<int> efxB;
	ofParameter<int> flipA;
	ofParameter<int> flipB;
	ofParameter<int> black;



};

class MixerFboWrapper : public ofxLayer::Layer
{
public:
	OFX_LAYER_DEFINE_LAYER_CLASS(MixerFboWrapper);

	void setup(MainMixer * mixer,int  width, int height) {
		this->mixer = mixer;
		wrapper.allocate(width, height);
	}
	virtual void draw() override {
		wrapper.draw(0,0);
	}
	virtual void update() override {
		mixer->update();
		wrapper.begin();
		ofClear(0, 0);
		mixer->draw();
		wrapper.end();
	}
	ofFbo wrapper;
private:
	MainMixer * mixer;
	
};
