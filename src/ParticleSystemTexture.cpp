#include "ParticleSystemTexture.h"



ParticleSystemTexture::ParticleSystemTexture() : VjObject("ParticleSystemTexture")
{
	system = new ParticleSystem(5000);
	this->addParameter(system->getParameterGroup());
}


ParticleSystemTexture::~ParticleSystemTexture()
{
	delete system;
}

void ParticleSystemTexture::setup()
{
	//fbo.allocate(this->ofGetWidth(), this->ofGetHeight());

	system->setup(this->ofGetWidth(), this->ofGetHeight());
}

void ParticleSystemTexture::update()
{
	system->update();

}

void ParticleSystemTexture::draw() 
{
	//fbo.draw(0, 0);
	//fbo.begin();
	//ofClear(0, 0, 0, 255);
	system->draw(0, 0);
	//fbo.end();
}
