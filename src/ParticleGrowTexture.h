#pragma once
#include "VjObject.h"
#include "ofxLayer.h"

using namespace ofxLayer;


class GrowParticle 
{
public:
	GrowParticle();
	void setup(ofVec2f * m_base, ofVec2f m_direction, ofVec2f offset,
	float* directionRotateSpeed, float* offset_rotateSpeed,float* radius, float m_timeout, 
		float time = 0, float size = 0.01);
	void update(float deltatime);
	void draw() const;
	ofColor color;
private:
	//resetBasePosition
	ofVec2f *base;
	ofVec2f baseinv;
	//direction ofMovement
	ofVec2f direction;
	ofVec2f directionStart;
	//current position
	ofVec2f position;
	ofVec2f positioninv;
	//current offset for shape
	ofVec2f offset;


	//fadeout and reset timeout
	float time = 0;
	float timeout = 0;

	float* rotate_direction;
	float* rotate_offset;
	float* radius;

	float size = 0.01;

	void updateInvBase();
	float calcD() const;
};


class ParticleGrowTexture :
	public ofxLayer::Layer, public VjObject
{
public:

	OFX_LAYER_DEFINE_LAYER_CLASS(ParticleGrowTexture);


	ParticleGrowTexture();
	~ParticleGrowTexture();

	virtual void setup() override;
	virtual void update() override;
	virtual void draw()  override;

private:
	float lasttime = 0;
	float time = 0;
	float timeX = 0;
	float timeY = 0;

	ofVec2f base[5];
	float rotate_direction = 30;
	float rotate_offset = 60;
	float radius_part = 3;
	GrowParticle p[5][5][60];
	//ofFbo fbo;
	void render();

	ofParameter<float> speed;
	ofParameter<float> speedRot;
	ofParameter<float> ampX;
	ofParameter<float> ampY;
	ofParameter<float> speedX;
	ofParameter<float> speedY;
	ofParameter<float> radius;

	ofColor color = ofColor(255);

	ofParameter<float> rgb_r;
	ofParameter<float> rgb_g;
	ofParameter<float> rgb_b;



};

