#pragma once
#include "TextureGen.h"
class SphereGrow :
	public TextureGen
{
public:
	SphereGrow(string name = "SphereGrow");
	~SphereGrow();

	virtual void setup(float width, float height) override;
	virtual ofTexture& getTextureRef()	override;

	virtual void update() override;
	virtual void draw(float x, float y, float w, float h) const override;
	virtual void draw(float x, float y) const override;

private:

	float edge(float in);

	float lasttime = 0;
	float rmsTime = 0;
	static const size_t sphereCount = 10;
	vector <ofIcoSpherePrimitive> sphere;
	float phase;
	ofParameter<float> grow = 0.3f;
	ofParameter<float> size = 0.1;
	ofShader shader;
	ofFbo fbo;
};

