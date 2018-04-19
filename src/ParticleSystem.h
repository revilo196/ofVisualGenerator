
#pragma once
#include "VjObject.h"


/*
	Particle that is part of a simulation and can simulate itself in 3D space.
	You can apply Forces or set A velocity
*/
class Particle {
public:
	Particle() {}
	~Particle() {}

	///<summary>init particle and connect the pointers to the ParticleSystem Simulation</summary>
	///<param name='pos'>pointer to where to save position</param>  
	///<param name='color'>pointer to where to save color</param>  
	///<param name='posMax'>Max xyz position in SimulationBox</param>  
	///<param name='posMin'>/Min xyz position in SimulationBox</param>  
	///<param name='time'>global time ptr</param>  
	///<param name='sair'>global air resistance factor</param>  
	void setup(ofVec3f * pos, ofFloatColor * color, ofVec3f posMax, ofVec3f posMin, float *time, float * sair);

	void update();
	//draw particle as Quad
	void draw() const;
	//Apply Force to the Particle
	void applyForce(ofVec3f force);
	//Apply rotational force to the Particle
	void applyForceRot(ofVec3f force);
	//Apply force to the Particle according to a Perlin Noise Vector Feld
	void applyForceNoise(float amplitude, float scale);
	//Set a specifiv Velocity
	void setVelocity(ofVec3f vel);
	//Set a specific Rotation Velocity
	void setVelocityRot(ofVec3f velRot);

	//get current position
	ofVec3f getPos();
	//get current rotaion
	ofVec3f getRot();
private:

	//pointer where to store calculated color
	ofFloatColor * color;
	//pointer where to store calculated position
	ofVec3f * pos;

	//Velocity
	ofVec3f vel;
	//Acceleration
	ofVec3f acc;

	//Rotation
	ofVec3f rot;
	//Rotation speed
	ofVec3f vrt;
	//Rotation Acceleration
	ofVec3f art;

	//Max xyz position in SimulationBox
	ofVec3f posMax;
	//Min xyz position in SimulationBox
	ofVec3f posMin;
	//Center of the SimulationBox
	ofVec3f midVec;

	//pointer to where to get the current time
	float *time;
	//pointer to where to get the velocity factor
	float *velfac;

};

/// Particle System Simulation with ofParametres for interaction
class ParticleSystem :
	public ofBaseDraws, public ofBaseUpdates, public VjObject
{
public:
	ParticleSystem(size_t count = 5000, string name = "Particle Simulation");
	~ParticleSystem();

	virtual void update() override;
	virtual void draw(float x, float y, float w, float h) const override;
	virtual void draw(float x, float y) const override;

	virtual void setup(float width, float height);

	virtual float getHeight() const override { return height; }
	virtual float getWidth() const override { return width; }

private:

	//count of particles
	size_t count = 10000;
	//particle position storage
	ofVec3f *vertex;
	//particle color storage
	ofFloatColor *color;
	ofIndexType *indices;

	//Shader with geometry shader
	ofShader shader;
	ofVbo vbo;

	float time;
	float m_partVel;
	vector<Particle> system;
	float width;
	float height;
	
	ofParameter<float> speed;
	ofParameter<float> forceAmplitude;
	ofParameter<float> scale;
	ofParameter<bool> add;
	ofParameter<bool> remove;
	ofParameter<float> partVel; 
};









//--------------------------------------WIP-------------------------








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
