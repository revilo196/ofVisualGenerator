#include "WaveMeshOverlay.h"


WaveMeshOverlay::WaveMeshOverlay(string name) : Overlay(name)
{

	addParameter(speedFront.set("speedFront", 0.5f, -1.0f, 1.0f));
	addParameter(speedLeft.set("speedLeft", 0.5f, -1.0f, 1.0f));
	addParameter(speedZ.set("speedZ", 0.5f, 0.0f, 10.0f));
	addParameter(amplitude.set("amplidude", 128.0f, 0.0f, 512.0f));
	addParameter(wire.set("wire", true));
	addParameter(rotateZ.set("rotateZ", 3.0f, 0.0f, 30.0f));
	this->res = 128;

}

WaveMeshOverlay::~WaveMeshOverlay()
{
}

void WaveMeshOverlay::setResulution(int res)
{
	this->res = res;
}

void WaveMeshOverlay::setup(float width, float height)
{
	Overlay::setup(width, height);

	fbo.allocate(width, height);

	shader.load("waveMeshOverlay");

	plane.set(width * 2, height * 4);
	plane.setPosition(0, 0, 0);
	plane.setResolution(res, res * 2);
}

ofTexture & WaveMeshOverlay::getTextureRef()
{
	return fbo.getTextureReference();
}

void WaveMeshOverlay::update()
{
	float deltatime = ofGetElapsedTimef() - lasttime;
	lasttime = ofGetElapsedTimef();


	time[0] += deltatime * speedLeft.get()*0.1;
	time[1] += deltatime * speedFront.get()*0.1;
	time[2] += deltatime * speedZ.get() * 0.01;

	render();
}

void WaveMeshOverlay::render()
{
	float cx = getWidth() / 2.0;
	float cy = getHeight() / 2.0;

	fbo.begin();
	ofClear(0, 0, 0, 255);
	shader.begin();

	ofTranslate(cx, cy - 250, -100);
	ofRotateX(60);
	ofRotateZ(rotateZ);
	ofTranslate(0, -cy, -30);

	shader.setUniform3f("offset", time[0], time[1], time[2]);
	shader.setUniform1f("amp", amplitude);
	shader.setUniform1f("fadewidth", 800);
	shader.setUniformTexture("mtex0", this->textureIn, 1);
	shader.setUniform2f("textureSizem", this->textureIn.getWidth(), this->textureIn.getHeight());


	plane.draw();


	shader.end();
	fbo.end();
}

void WaveMeshOverlay::draw(float x, float y, float w, float h) const
{
	fbo.draw(x, y, w, h);
}

void WaveMeshOverlay::draw(float x, float y) const
{
	fbo.draw(x, y);
}



