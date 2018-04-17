#include "ParticleSystem.h"



ParticleSystem::ParticleSystem() : VjObject("System")
{

}


ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::update()
{
	for (int i = 0; i < system.size(); i++) {
		system[i].applyForceNoise();
		system[i].update();
	}
}

void ParticleSystem::draw(float x, float y, float w, float h) const
{
	for (int i = 0; i < system.size(); i++) {
		system[i].draw();
	}
}

void ParticleSystem::draw(float x, float y) const
{
	ofCamera cam;
	cam.begin();
	for (int i = 0; i < system.size(); i++) {
		system[i].draw();
	}
	
	
	//ofDrawLine(0, 0,0, -1, -1,-1);

	ofDrawBox(0,0,-10,1);

	cam.end();

}

void ParticleSystem::setup(float width, float height)
{
		this->height = height;
		this->width = width;

		system.resize(1000);
		for (int i = 0; i < 1000; i++) {
			system[i] = Particle();
			system[i].setup(ofVec3f(ofRandomf()*20, ofRandomf()*20, -10 - ofRandomuf()*50),
				ofVec3f(20,20,-10), ofVec3f(-20,-20,-75));
		}

}

void Particle::update()
{
	this->vel += acc- (vel.normalize()*(vel.lengthSquared())*0.5);
	this->pos += vel*0.1;
	this->acc = acc * 0;

	this->vrt += art; // TODO max / damping
	this->rot += vrt;
	this->art = art * 0;

	if (pos.x < posMin.x) {
		pos.x = posMax.x;
	}
	if (pos.y < posMin.y) {
		pos.y = posMax.y;
	}
	if (pos.z < posMin.z) {
		pos.z = posMax.z;
	}
	if (pos.x > posMax.x) {
		pos.x = posMin.x;
	}
	if (pos.y > posMax.y) {
		pos.y = posMin.y;
	}
	if (pos.z > posMax.z) {
		pos.z = posMin.z;
	}

}

void Particle::setup(ofVec3f pos, ofVec3f posMax, ofVec3f posMin)
{
	this->pos = pos;
	this->posMax = posMax;
	this->posMin = posMin;
}

void Particle::draw() const
{
	
	//ofSetColor(255,255,255, -0.186 * ((pos.z - 38)*(pos.z - 38)) + 255);

	ofDrawBox(pos,1);
}

void Particle::applyForce(ofVec3f force)
{
	acc += force;
}

void Particle::applyForceRot(ofVec3f force)
{
	art += force;
}

void Particle::applyForceNoise()
{
	float scale = 50;
	float x = ofNoise(pos.x / scale, pos.y / scale, pos.z / scale, 1.0);
	float y = ofNoise(pos.x / scale, pos.y / scale, pos.z / scale, 100.0);
	float z = ofNoise(pos.x / scale, pos.y / scale, pos.z / scale, -100.0);

	ofVec3f force = ofVec3f(x, y, z);
	applyForce(force);

}

void Particle::setVelocity(ofVec3f vel)
{
	this->vel = vel;
}

void Particle::setVelocityRot(ofVec3f velRot)
{
	this->vrt = velRot;
}

ofVec3f Particle::getPos()
{
	return rot;
}

ofVec3f Particle::getRot()
{
	return rot;
}
