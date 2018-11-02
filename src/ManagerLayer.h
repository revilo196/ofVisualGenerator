#pragma once

#include "ofxLayerManager.h"
#include "ofxLayer.h"
#include "ofxGui.h"
#include "VjObject.h"


using namespace ofxLayer;

class ManagerLayer : public ofxLayer::Layer
{
public:
	static int globalMngLayCont;

	OFX_LAYER_DEFINE_LAYER_CLASS(ManagerLayer);

	ManagerLayer() {};
	~ManagerLayer() {};

	virtual void setup() override;
	virtual void update() override;
	virtual void draw()  override;
	void selfInit();
	void setupParamRouter();
	template <typename T > T* createLayer(float defalut_alpha = 0);

	ofParameterGroup fader;
	ofParameterGroup config;
	ofParameterGroup all;

	ofParameterGroup paraRouter;
	ofParameter<int> routTo;


private:
	void switchRoutionTo(int &val);
	void updateParamRouter();
	void updateParamRouterf(float &f);
	void updateParamRouterb(bool &f);
	void updateParamRouterc(ofFloatColor &f);




	ofxLayer::Manager mng;

	size_t counter = 0;
	vector<ofxLayer::Layer*> textures;
	vector<ofParameterGroup> configs;
	vector<ofParameter<float>> alphafader;

};


