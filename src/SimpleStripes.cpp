#include "SimpleStripes.h"



SimpleStripes::SimpleStripes(string name) : TextureGen(name)
{
	addParameter(speed.set("speed",0.5, -5.0, 5.0));
	addParameter(freq.set("freq", 3, 0.0, 32));
	addParameter(tilt.set("tilt", 0, 0.0, 2));
	addParameter(thick.set("thick", 0.5, 0.0, 1.0));
	addParameter(smooth.set("smooth", 0.05, 0.0, 0.3));
}


SimpleStripes::~SimpleStripes()
{
}

void SimpleStripes::setup(float width, float height)
{
	TextureGen::setup(width, height);

	fbo.allocate(width, height);

	shader.load("shader.vert", "stripes.frag");

	plane.set(width , height );
	plane.setPosition(0, 0, 0);
	plane.setResolution(2,2);
}

ofTexture & SimpleStripes::getTextureRef()
{
	return fbo.getTexture();
}

void SimpleStripes::update()
{
	float deltatime = ofGetElapsedTimef() - lasttime;
	lasttime = ofGetElapsedTimef();

	time += deltatime * (speed);

	shader.begin();

	shader.setUniform1i("fullscreen", 1);
	shader.setUniform2f("resulution", getWidth(), getHeight());
	shader.setUniform1f("time", time);
	shader.setUniform1f("FREQUENCE", freq);
	shader.setUniform1f("TILT", tilt);
	shader.setUniform1f("THIKNESS", thick);
	shader.setUniform1f("SMOOTHNESS", smooth);

	shader.end();

	render();
}

void SimpleStripes::draw(float x, float y, float w, float h) const
{
	fbo.draw(x, y, w, h);
}

void SimpleStripes::draw(float x, float y) const
{
	fbo.draw(x, y);
}

void SimpleStripes::render()
{
	
	float cy = getHeight() / 2;
	float cx = getWidth() / 2;

	fbo.begin();

		ofClear(0, 0, 0, 255);

		ofTranslate(cx, cy);

		shader.begin();
			plane.draw();
		shader.end();

	fbo.end();
}
