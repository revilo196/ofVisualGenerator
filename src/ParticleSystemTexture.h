#pragma once
#include "TextureGen.h"
#include "ParticleSystem.h"

class ParticleSystemTexture :
	public TextureGen
{
public:
	ParticleSystemTexture(string name = "ParticleSystemTexture");
	~ParticleSystemTexture();

	virtual void setup(float width, float height) override;
	virtual ofTexture& getTextureRef()	override;

	virtual void update() override;
	virtual void draw(float x, float y, float w, float h) const override;
	virtual void draw(float x, float y) const override;

private:
	ParticleSystem * system;
	ofFbo fbo;
};

