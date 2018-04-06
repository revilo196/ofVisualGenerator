#include "SimpleDots.h"

SimpleDots::SimpleDots(string name) : TextureGen(name)
{
}

SimpleDots::~SimpleDots()
{
}

void SimpleDots::setup(float width, float height)
{
	TextureGen::setup(width*3, height*3);

	fbo.allocate(width*3, height*3);

	for (int i = 0; i < RANDARR; i++) {
		randArray[i] = (ofRandomuf() * 0.5) + 0.5;
	}

}

ofTexture & SimpleDots::getTextureRef()
{
	return fbo.getTextureReference();
}

void SimpleDots::update()
{
	fbo.begin();

	ofClear(0, 0, 0, 255);

	int xres = getWidth() / main_size;
	int yres = getHeight() / main_size;

	ofPushStyle();
	ofSetColor(255);
	ofSetCircleResolution(4);
	ofScale(0.333, 0.333);

	for (int i = 0; i < xres; i++)
	{
		for (int j = 0; j < yres; j++)
		{
			ofDrawCircle((main_size/2) + i * main_size, (main_size/2) + j * main_size, (main_size/5) * randArray[(i*j)%RANDARR]);
		}

	}
	
	ofPopStyle();
	

	fbo.end();
}

void SimpleDots::draw(float x, float y, float w, float h) const
{
	fbo.draw(x, y, w, h);
}

void SimpleDots::draw(float x, float y) const
{
	fbo.draw(x, y);
}
