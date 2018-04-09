#pragma once
#include "TextureGen.h"
#include "ofxAnimatableFloat.h"

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
	float time_stripes;


	ofShader shader;
	ofFbo fbo;
	vector<ofBoxPrimitive> boxes;
	vector<ofVec3f> rotations;
	vector<float> speeds;
	
	ofParameter<float> speed;
	ofParameter<float> speedStripes;
	ofParameter<float> thikStripes;
	ofParameter<float> tiltStripes;
	ofParameter<float> addSpeed = 0.5;
	ofParameter<bool> out = false;

	ofxAnimatableFloat radius;

};

