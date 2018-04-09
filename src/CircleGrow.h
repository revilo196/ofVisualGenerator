#pragma once
#include "TextureGen.h"

class CircleGrow :
	public TextureGen
{
public:
	CircleGrow(string name = "CircleGrow");
	~CircleGrow();

	virtual void setup(float width, float height) override;
	virtual ofTexture& getTextureRef()	override;
	virtual void update() override;
	virtual void draw(float x, float y, float w, float h) const override;
	virtual void draw(float x, float y) const override;

private:
	float lasttime;
	float time;
	float timerot;
	void setupPoints();

	float edge(float in);

	ofFbo fbo;
	ofShader shader;

	vector <ofPoint> points;

	ofParameter<float> bogen = 50.0f;
	ofParameter<float> grow = 0.2f;
	ofParameter<float> rotate = 50.0f;
	ofParameter<float> size = 400.0f;
	ofParameter<int> res = 50;
	ofParameter<float> thick = 7.0f;
	ofParameter<ofColor> color;


};

