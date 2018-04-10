#pragma once
#include "TextureGen.h"

#define RANDARR 512

class SimpleDots :
	public TextureGen
{
public:
	explicit SimpleDots(string name = "SimpleDots");
	~SimpleDots();

	virtual void setup(float width, float height) override;
	virtual ofTexture& getTextureRef()	override;
	virtual void update() override;
	virtual void draw(float x, float y, float w, float h) const override;
	virtual void draw(float x, float y) const override;

private:
	ofFbo fbo;
	float lasttime = 0;
	float time = 0;
	int main_size = 20;

	float randArray[RANDARR];

};

