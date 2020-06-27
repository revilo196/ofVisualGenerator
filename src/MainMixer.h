#pragma once
#include "VjObject.h"

class MainMixer
{
public:
	static int globalMainMixCont;


	MainMixer();
	~MainMixer();

	void setup(ofFbo  l1, ofFbo  l2, int w, int h);
	void update();
	void draw();


	ofParameterGroup all;

private:
	int width;
	int height;
	ofFbo l1;
	ofFbo l2;
	ofPlanePrimitive fullQuad;
	ofShader shader;
	ofShader blurXShader;
	ofShader blurYShader;
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

class MixerFboWrapper
{
public:


	void setup(MainMixer * mixer,int  width, int height) {
		this->mixer = mixer;
		wrapper.allocate(width, height);
	}
	void draw(){
		wrapper.draw(0,0);
	}
	void update(){
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
