#pragma once
#include "TextureGen.h"
class SimpleStripes :
	public TextureGen
{
public:
	explicit SimpleStripes(string name = "SimpleStripes");
	~SimpleStripes();

	virtual void setup(float width, float height) override;
	virtual ofTexture& getTextureRef()	override;
	virtual void update() override;
	virtual void draw(float x, float y, float w, float h) const override;
	virtual void draw(float x, float y) const override;

private:
	void render();
	float lasttime = 0;
	float time = 0;
	ofPlanePrimitive plane;
	ofFbo fbo;
	ofShader shader;

	ofParameter<float> speed;
	ofParameter<float> freq;
	ofParameter<float> tilt;
	ofParameter<float> thick;
	ofParameter<float> smooth;


	
};

