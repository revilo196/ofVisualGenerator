#include "StripeCubes.h"



StripeCubes::StripeCubes(string name) : TextureGen(name)
{
	addParameter(speed.set("speed", 0.5, 0.0, 3.0));
}

StripeCubes::~StripeCubes()
{
}

void StripeCubes::setup(float width, float height)
{
	TextureGen::setup(width, height);
	fbo.allocate(width, height);
	shader.load("shader.vert", "stripes.frag");
	setCubes(5);
}

ofTexture & StripeCubes::getTextureRef()
{
	return fbo.getTexture();
}

void StripeCubes::update()
{
	deltatime = lasttime - ofGetElapsedTimef();
	lasttime = ofGetElapsedTimef();

	time += deltatime * speed;

	shader.begin();
	shader.setUniform1i("fullscreen", 0);
	shader.setUniform1f("time", time);
	shader.setUniform1f("FREQUENCE", 5);
	shader.setUniform1f("TILT", 0);
	shader.setUniform1f("THIKNESS", 0.5);
	shader.setUniform1f("SMOOTHNESS", 0.02);
	shader.end();

	render();
}

void StripeCubes::draw(float x, float y, float w, float h) const
{
	fbo.draw(x, y, w, h);
}

void StripeCubes::draw(float x, float y) const
{
	fbo.draw(x,y);
}

void StripeCubes::setCubes(int count)
{
	for (int i = 0; i < count; i++) {
		boxes.push_back(ofBoxPrimitive(0.4, 0.4, 0.4));
		rotations.push_back(ofVec3f(ofRandomf(), ofRandomf(), ofRandomf()));
		speeds.push_back(ofRandomf());
	}
}

void StripeCubes::rotateBoxes()
{
	for (int i = 0; i < boxes.size(); i++) {
		boxes[i].rotate((speeds[i] * deltatime + addSpeed) * speed, rotations[i]);
	}
}

void StripeCubes::drawBoxes()
{
	
	ofRotate(time * 5);
	for (int i = 0; i < boxes.size(); i++) {
		ofRotate(70);
		ofTranslate(0.5, 0, 0);
		boxes[i].draw();
		ofTranslate(-0.5, 0, 0);
	}
	ofTranslate(0.5, 0, 0);

}

void StripeCubes::render()
{
	fbo.begin();
	glEnable(GL_DEPTH_TEST);
	ofClear(0, 0, 0, 255);
	

	translateMidFlipScale();

	shader.begin();


	rotateBoxes();

	drawBoxes();

	shader.end();
	glDisable(GL_DEPTH_TEST);
	fbo.end();
}

