#pragma once
#include "VjObject.h"

class Particle {
public:
	Particle() {}
	~Particle() {}


	void update();
	void setup(ofVec3f pos, ofVec3f posMax, ofVec3f posMin);
	void draw() const;
	void applyForce(ofVec3f force);
	void applyForceRot(ofVec3f force);
	void applyForceNoise();
	void setVelocity(ofVec3f vel);
	void setVelocityRot(ofVec3f velRot);

	ofVec3f getPos();
	ofVec3f getRot();
private:


	ofVec3f pos;
	ofVec3f vel;
	ofVec3f acc;

	ofVec3f rot;
	ofVec3f vrt;
	ofVec3f art;

	ofVec3f posMax;
	ofVec3f posMin;

	

};

class ParticleSystem :
	public ofBaseDraws, public ofBaseUpdates, public VjObject
{
public:
	ParticleSystem();
	~ParticleSystem();

	

	virtual void update() override;
	virtual void draw(float x, float y, float w, float h) const override;
	virtual void draw(float x, float y) const override;

	virtual void setup(float width, float height);


	virtual float getHeight() const override { return height; }
	virtual float getWidth() const override { return width; }


private:
	vector<Particle> system;
	float width;
	float height;
	
};

