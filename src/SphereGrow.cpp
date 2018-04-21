#include "SphereGrow.h"



SphereGrow::SphereGrow() : VjObject("SphereGrow")
{
	const int res = 1;
	sphere.resize(sphereCount);
	//radius.resize(sphereCount);

	for (int i = 0; i < sphereCount; i++) {
		float radius = static_cast<float>(i) / static_cast<float>(sphereCount);
		sphere[i].set(radius*size , res);
		sphere[i].setMode(OF_PRIMITIVE_TRIANGLES);
	}

	addParameter(grow.set("grow", 0.1, -0.3, 0.3));
	addParameter(size.set("size", 0.5, 0.02, 3.0));
}


SphereGrow::~SphereGrow()
{
}

void SphereGrow::setup()
{
	
	//fbo.allocate(this->ofGetWidth(), this->ofGetHeight());
	shader.load("shader.vert", "shader.frag");
}


float SphereGrow::edge(float in)
{

	if (in > 1.0)
		return in - 1.0;
	else if (in < -1.0)
		return in + 1.0;
	else
		return in;
}

void SphereGrow::update()
{
	float deltatime = ofGetElapsedTimef() - lasttime;
	lasttime = ofGetElapsedTimef();

	phase += deltatime * grow*0.5;
	phase = edge(phase);

	//fbo.begin();
	
	//fbo.end();
}



void SphereGrow::draw()
{
	//fbo.draw(0, 0);

	//ofClear(0, 0, 0, 255);
	shader.begin();

	translateMidFlipScale();
	ofRotateZ(ofGetElapsedTimef());

	for (int i = 0; i < sphereCount; i++) {
		float myphase = phase + static_cast<float>(i) / static_cast<float>(sphereCount);
		myphase = edge(myphase);
		sphere[i].setRadius(size * myphase);
		sphere[i].setGlobalPosition(0.2 + myphase, 0.2 + myphase, -2);
		ofRotateX(rmsTime * 0.5 + 3);
		ofRotateY(rmsTime * 0.2 + 2);
		ofRotateY(ofGetElapsedTimef() / 2 + 3);
		ofRotateZ(5);
		ofSetColor((1 - myphase) * 255);
		sphere[i].drawWireframe();
	}

	shader.end();
}

