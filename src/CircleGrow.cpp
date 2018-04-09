#include "CircleGrow.h"


CircleGrow::CircleGrow(string name) : TextureGen(name)
{
	addParameter(bogen.set("bogen", 50.0, 0, 360));
	addParameter(grow.set("grow", 0.2, -2, 2));
	addParameter(rotate.set("rotate", 50.0, 0, 360));
	addParameter(size.set("size", 1, 0, 3));
	addParameter(res.set("res", 50, 2, 120));
	addParameter(thick.set("thick", 0.02, 0, 0.5));
	addParameter(color);
}

CircleGrow::~CircleGrow()
{
}

void CircleGrow::setup(float width, float height)
{
	TextureGen::setup(width, height);

	fbo.allocate(width, height);
	setupPoints();
}

void CircleGrow::setupPoints() {
	for (int i = 0; i < 20; i++) {
		points.push_back(ofPoint(ofRandomf(), ofRandomf()));
	}
}

float CircleGrow::edge(float in)
{

	if (in > 1.0) 
		return in - 1.0;
	else if (in < -1.0)
		return in + 1.0;
	else
		return in;
}

ofTexture & CircleGrow::getTextureRef()
{
	return fbo.getTexture();
}

void CircleGrow::update()
{
	float deltatime = ofGetElapsedTimef() - lasttime;
	lasttime = ofGetElapsedTimef();

	time += deltatime * grow;
	time = edge(time);
	timerot += deltatime * rotate;

	fbo.begin();

	ofClear(0, 0, 0, 255);
	translateMidFlipScale();


	for (int i = 0; i < points.size(); i++) {
		float myPhase = time + static_cast<float>(i) / static_cast<float>(points.size());
		myPhase = edge(myPhase);



		float radius = myPhase * size;
		ofColor c = color;
		c.a = MIN(255, 512 * (1 - myPhase * myPhase));

		float myRotate = timerot + ofNoise(static_cast<float>(i) / static_cast<float>(points.size())) * 1000;
		ofPath curve;
		curve.arc(points[i], radius, radius, myRotate, myRotate+bogen);
		curve.arcNegative(points[i], radius-thick, radius- thick, myRotate + bogen, myRotate);
		curve.close();
		curve.setArcResolution(res);
		curve.setFillColor(c);
		curve.setFilled(true);
		curve.draw();

	}

	fbo.end();
}

void CircleGrow::draw(float x, float y, float w, float h) const
{
	fbo.draw(x, y, w, h);
}

void CircleGrow::draw(float x, float y) const
{
	fbo.draw(x, y);
}
