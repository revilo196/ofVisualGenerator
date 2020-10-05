#include "CircleGrow.h"


CircleGrow::CircleGrow() : VjObject("CircleGrow")
{
	addParameter(bogen.set("bogen", 50.0, 0, 360));
	addParameter(grow.set("grow", 0.2, -2, 2));
	addParameter(rotate.set("rotate", 50.0, 0, 360));
	addParameter(size.set("size", 1, 0, 3));
	addParameter(res.set("res", 50, 2, 120));
	addParameter(thick.set("thick", 0.02, 0, 0.5));
	addParameter(rgb_r.set("rgb_r", 255, 0, 255));
	addParameter(rgb_g.set("rgb_g", 255, 0, 255));
	addParameter(rgb_b.set("rgb_b", 255, 0, 255));

	this->color.r = rgb_r ;
	this->color.g = rgb_g ;
	this->color.b = rgb_b ;


	//cout << color.getEscapedName() << endl;
}

CircleGrow::~CircleGrow()
{
}

void CircleGrow::setup()
{
	//fbo.allocate(this->ofGetWidth(), this->ofGetHeight());
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

void CircleGrow::update()
{
	this->updateParms();

	this->color.r = rgb_r ;
	this->color.g = rgb_g ;
	this->color.b = rgb_b ;

	float deltatime = ofGetElapsedTimef() - lasttime;
	lasttime = ofGetElapsedTimef();

	time += deltatime * grow;
	time = edge(time);
	timerot += deltatime * rotate;

	
}

void CircleGrow::draw()
{

	//ofClear(0, 0, 0, 255);

	translateMidFlipScale();


	for (int i = 0; i < points.size(); i++) {
		float myPhase = time + static_cast<float>(i) / static_cast<float>(points.size());
		myPhase = edge(myPhase);



		float radius = myPhase * size;
		ofColor c = color;
		c.a = MIN(255, 512 * (1 - myPhase * myPhase));

		float myRotate = timerot + ofNoise(static_cast<float>(i) / static_cast<float>(points.size())) * 1000;
		ofPath curve;
		curve.arc(points[i], radius, radius, myRotate, myRotate + bogen);
		curve.arcNegative(points[i], radius - thick, radius - thick, myRotate + bogen, myRotate);
		curve.close();
		curve.setArcResolution(res);
		curve.setFillColor(c);
		curve.setFilled(true);
		curve.draw();

	}

}

