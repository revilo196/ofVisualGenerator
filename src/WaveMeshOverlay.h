#pragma once
#include "Overlay.h"
class WaveMeshOverlay :
	public Overlay
{
public:
	explicit WaveMeshOverlay(string name = "WaveMeshOverlay");
	~WaveMeshOverlay();

	virtual void setup(float width, float height) override;
	virtual ofTexture& getTextureRef()	override;
	virtual void update() override;
	virtual void draw(float x, float y, float w, float h) const override;
	virtual void draw(float x, float y) const override;
	virtual void setResulution(int res);

private:
	ofFbo fbo;

	virtual void render();
	ofPlanePrimitive plane;
	ofShader shader;
	float lasttime;
	ofVec3f time;
	ofParameter<float> speedFront = 0.5f;
	ofParameter<float> speedLeft = 0.5f;
	ofParameter<float> speedZ = 0.5f;
	ofParameter<bool> wire = true;
	ofParameter<float> amplitude = 128.0f;
	ofParameter<float> rotateZ = 8.0f;
	int res = 256;

};

