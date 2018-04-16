#include "ParticleSystem.h"



ParticleSystem::ParticleSystem()
{
}


ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::update()
{
}

void ParticleSystem::draw(float x, float y, float w, float h) const
{
}

void ParticleSystem::draw(float x, float y) const
{
}

void Particle::update()
{
	this->vel += acc - (vel.normalize()*(vel.lengthSquared())*0.5);
	this->pos += vel;
	this->acc = acc * 0;

	this->vrt += art; // TODO max / damping
	this->rot += vrt;
	this->art = art * 0;

}

void Particle::setup(ofVec3f pos)
{
	this->pos = pos;
}

void Particle::draw()
{
	ofDrawBox(pos,2);
}

void Particle::applyForce(ofVec3f force)
{
	acc += force;
}

void Particle::applyForceRot(ofVec3f force)
{
	art += force;
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
