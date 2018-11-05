#pragma once

#include "ofxLayer.h"
#include "VjObject.h"

using namespace ofxLayer;

enum RenderMode
{
	RM_WIRE,
	RM_POINT,
	RM_SURFACE
};

class WaveMeshTexture : 
	public ofxLayer::Layer, public VjObject
{
public:
	OFX_LAYER_DEFINE_LAYER_CLASS(WaveMeshTexture);

	WaveMeshTexture();
	~WaveMeshTexture();

	void setResulution(int res);

	virtual void setup() override;
	virtual void update() override;
	virtual void draw() override;

	void setRenderMode(RenderMode rm);


protected:
	ofShader shader;

private:
	
	ofPlanePrimitive plane;
	void render();
	float lasttime = 0;
	ofVec3f time;
	//ofFbo fbo;
	ofParameter<RenderMode> renderMode = RM_WIRE;
	ofParameter<float> speedFront = 0.5f;
	ofParameter<float> speedLeft = 0.5f;
	ofParameter<float> speedZ = 0.5f;
	ofParameter<bool> wire = true;
	ofParameter<float> amplitude = 128.0f;
	ofParameter<float> rotateZ = 8.0f;
	int res = 256;

};

