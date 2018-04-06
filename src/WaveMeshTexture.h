#pragma once
#include "TextureGen.h"

enum RenderMode
{
	RM_WIRE,
	RM_POINT,
	RM_SURFACE
};

class WaveMeshTexture : public TextureGen
{
public:
	WaveMeshTexture(string name = "WaveMeshTexture");
	~WaveMeshTexture();

	void setResulution(int res);

	virtual void setup(float width, float height) override;
	virtual ofTexture& getTextureRef()	override;
	virtual void update() override;
	virtual void draw(float x, float y, float w, float h) const override;
	virtual void draw(float x, float y) const override;
	void setRenderMode(RenderMode rm);
	//void overrideShader(string vertexShader, string fragmentShader);

protected:
	ofShader shader;

private:
	
	ofPlanePrimitive plane;
	void render();
	float lasttime;
	ofVec3f time;
	ofFbo fbo;
	ofParameter<RenderMode> renderMode = RM_WIRE;
	ofParameter<float> speedFront = 0.5f;
	ofParameter<float> speedLeft = 0.5f;
	ofParameter<float> speedZ = 0.5f;
	ofParameter<bool> wire = true;
	ofParameter<float> amplitude = 128.0f;
	ofParameter<float> rotateZ = 8.0f;
	int res = 256;

};

