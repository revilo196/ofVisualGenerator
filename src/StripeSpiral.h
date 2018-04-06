#pragma once
#include "TextureGen.h"
class StripeSpiral :
	public TextureGen
{
public:
	StripeSpiral(string name = "StripeSpiral");
	~StripeSpiral();

	virtual void setup(float width, float height) override;
	virtual ofTexture& getTextureRef()	override;
	virtual void update() override;
	virtual void draw(float x, float y, float w, float h) const override;
	virtual void draw(float x, float y) const override;

private:
	float time;
	float lasttime;

	void render();
	ofFbo fbo;
	ofShader shader;
	ofPlanePrimitive plane;
	
	ofParameter<float> speed;
	ofParameter<int> edges;
	ofParameter<int> circles;
	ofParameter<float> distance;
	ofParameter<float> thik = 0.3;
	ofParameter<float> stripPhaseSpeed;
	ofParameter<float> stripCount;
	ofParameter<float> stripTilt;
	ofParameter<float> stripRot;


};	


