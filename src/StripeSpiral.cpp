#include "StripeSpiral.h"



StripeSpiral::StripeSpiral(string name) : TextureGen(name)
{
	addParameter(speed.set("speed", 0.5, -1, 1));
	addParameter(edges.set("edges", 8, 2, 16));
	addParameter(circles.set("circles", 20, 5, 128));
	addParameter(distance.set("distance", 16, 2, 64));
	addParameter(thik.set("THIKNESS", 0.3, 0.0, 1.0));
	addParameter(stripPhaseSpeed.set("stripPhaseSpeed", 0.3, 0.0, 2.0));
	addParameter(stripCount.set("stripCount", 10.0, 3.0, 30.0));
	addParameter(stripTilt.set("stripTilt", 0.0, 0.0, 1.0));
	addParameter(stripRot.set("stripRot", 0.0, 0.0, 1.0));





}


StripeSpiral::~StripeSpiral()
{
}

void StripeSpiral::setup(float width, float height)
{
	TextureGen::setup(width, height);

	fbo.allocate(width, height);


	shader.load("shader.vert", "stripes.frag");

	plane.set(1, 2);
	plane.setPosition(0, 0, 0);
	plane.setResolution(2, 2);
	
}

ofTexture & StripeSpiral::getTextureRef()
{
	return fbo.getTexture();
}

void StripeSpiral::update()
{

	float deltatime = ofGetElapsedTimef() - lasttime;
	lasttime = ofGetElapsedTimef();

	time += deltatime * (speed);

	shader.begin();

	shader.setUniform1i("fullscreen", 0);

	shader.setUniform1f("FREQUENCE", stripCount);
	shader.setUniform1f("TILT", stripTilt + (sinf(time)*stripRot));
	shader.setUniform1f("THIKNESS", thik);
	shader.setUniform1f("SMOOTHNESS", 0.06);

	shader.end();


	render();
}

void StripeSpiral::draw(float x, float y, float w, float h) const
{
	fbo.draw(x, y, w, h);
}

void StripeSpiral::draw(float x, float y) const
{
	fbo.draw(x, y);
}

void StripeSpiral::render()
{

	float cx = getWidth() / 2;
	float cy = getHeight() / 2;

	fbo.begin();
	ofClear(0, 0, 0, 255);

	translateMidFlipScale();

	shader.begin();
	glEnable(GL_DEPTH_TEST);

	 ofTranslate(0, 0, 1);


	 float angle = 360.0 / edges;


	for (int i = 0; i < (edges * circles) ; i++) {

		float zoff = (fmodf(time + (i/((edges*circles) / distance)), distance));

		if (zoff < 0) {
			zoff += distance;
		}

		ofRotate(angle);

		ofTranslate(0.9, 0, -zoff);
		ofPushStyle();
		ofSetColor(255 * (1 - (zoff / distance)));
		shader.setUniform1f("time", zoff * stripPhaseSpeed + 0.5);
		plane.draw();
		ofPopStyle();
		ofTranslate(-0.9, 0, zoff);
	}
	glDisable(GL_DEPTH_TEST);
	shader.end();
	fbo.end();

}