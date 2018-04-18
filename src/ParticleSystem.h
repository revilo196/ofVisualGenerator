#pragma once
#include "VjObject.h"

class Particle {
public:
	Particle() {}
	~Particle() {}

	void update();
	void setup(ofVec3f * pos , ofFloatColor * color, ofVec3f posMax, ofVec3f posMin, float *time);
	void draw() const;
	void applyForce(ofVec3f force);
	void applyForceRot(ofVec3f force);
	void applyForceNoise(float amplitude, float scale);
	void setVelocity(ofVec3f vel);
	void setVelocityRot(ofVec3f velRot);

	ofVec3f getPos();
	ofVec3f getRot();
private:
	//pointers to whre to save the simulation data
	ofFloatColor * color;
	ofVec3f * pos;

	ofVec3f vel;
	ofVec3f acc;

	ofVec3f rot;
	ofVec3f vrt;
	ofVec3f art;

	ofVec3f posMax;
	ofVec3f posMin;

	ofVec3f midVec;

	//pointer to where to get the current time
	float *time;
	float *velfac;
	float *air;

};

class BoxContainer {
public:
	BoxContainer() {};
	BoxContainer(ofVec3f cubemin, ofVec3f cubemax);
	~BoxContainer() {}
	ofVec3f cubemin;
	ofVec3f cubemax;


	bool contains(ofVec3f pos);
};

class QubeTree {
public:
	QubeTree(BoxContainer bound, int cap);
	~QubeTree();
	
	void insert(ofVec3f point);

private:
	int cap;
	BoxContainer boundary;
	vector<ofVec3f> points;
	bool subdivided = false;
	void subdivide();
	
	QubeTree * nwf;
	QubeTree * nef;
	QubeTree * sef;
	QubeTree * swf;
	QubeTree * nwb;
	QubeTree * neb;
	QubeTree * seb;
	QubeTree * swb;



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

	size_t count = 10000;
	ofVec3f *vertex;
	ofFloatColor *color;
	ofIndexType *indices;

	ofShader shader;
	ofVbo vbo;

	float time;
	float m_air;
	vector<Particle> system;
	float width;
	float height;
	
	ofParameter<float> speed;
	ofParameter<float> forceAmplitude;
	ofParameter<float> scale;
	ofParameter<bool> add;
	ofParameter<bool> remove;
	ofParameter<float> air; 
};

