#include "ParticleSystemTexture.h"



ParticleSystemTexture::ParticleSystemTexture() : VjObject("ParticleSystemTexture")
{
	system = new ParticleSystem(5000);

	addParameter(speed.set("speed", 0.002, -0.05, 0.05));
	addParameter(forceAmplitude.set("force", 1, -3, 3));
	addParameter(scale.set("scale", 1.0, 0.1, 5));
	addParameter(partVel.set("vel", 0.20, 0.05, 0.7));
	addParameter(rgb_r.set("rgb_r", 255, 0, 255));
	addParameter(rgb_g.set("rgb_g", 255, 0, 255));
	addParameter(rgb_b.set("rgb_b", 255, 0, 255));

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
	this->updateParms();

	system->colorParm.r = rgb_r / 255.0;
	system->colorParm.g = rgb_g / 255.0;
	system->colorParm.b = rgb_b / 255.0;
	system->speed = speed;
	system->forceAmplitude = forceAmplitude;
	system->scale = scale;
	system->partVel = partVel;


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
