#include "ParticleSystemTexture.h"



ParticleSystemTexture::ParticleSystemTexture(string name) : TextureGen(name)
{
	system = new ParticleSystem(5000);
	this->addParameter(system->getParameterGroup());
}


ParticleSystemTexture::~ParticleSystemTexture()
{
	delete system;
}

void ParticleSystemTexture::setup(float width, float height)
{
	fbo.allocate(width, height);

	system->setup(width, height);
}

ofTexture & ParticleSystemTexture::getTextureRef()
{
	return fbo.getTexture();
}

void ParticleSystemTexture::update()
{
	system->update();

	fbo.begin();
	ofClear(0, 0, 0, 255);

	system->draw(0, 0);
	fbo.end();

}

void ParticleSystemTexture::draw(float x, float y, float w, float h) const
{
	fbo.draw(x, y, w, h);
}

void ParticleSystemTexture::draw(float x, float y) const
{
	fbo.draw(x, y);
}
