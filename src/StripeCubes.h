#pragma once
#include "TextureGen.h"
class StripeCubes :
	public TextureGen
{
public:
	StripeCubes(string name = "StripeCubes");
	~StripeCubes();

	virtual void setup(float width, float height) override;
	virtual ofTexture& getTextureRef()	override;
	virtual void update() override;
	virtual void draw(float x, float y, float w, float h) const override;
	virtual void draw(float x, float y) const override;
	void setCubes(int count);

private:

	void rotateBoxes();
	void drawBoxes();
	void render();
	float deltatime;
	float lasttime;
	float time;

	ofShader shader;
	ofFbo fbo;
	vector<ofBoxPrimitive> boxes;
	vector<ofVec3f> rotations;
	vector<float> speeds;
	
	ofParameter<float> speed;
	ofParameter<float> addSpeed = 0.5;

};

