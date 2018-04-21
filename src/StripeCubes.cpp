#include "StripeCubes.h"



StripeCubes::StripeCubes() : VjObject("StripeCubes")
{
	addParameter(speed.set("speed", 0.5, 0.0, 3.0));
	addParameter(speedStripes.set("speedStripes", 0.5, 0.0, 3.0));
	addParameter(tiltStripes.set("tiltStripes", 0.5, 0.0, 3.0));
	addParameter(thikStripes.set("thikStripes", 0.5, 0.0, 1.0));
	addParameter(out.set("SendOut",false));

}

StripeCubes::~StripeCubes()
{
}

void StripeCubes::setup()
{

	//fbo.allocate(this->ofGetWidth(), this->ofGetHeight());
	shader.load("shader.vert", "stripes.frag");
	setCubes(5);
	radius.setup();
	radius.reset(0.5);
	radius.setCurve(EASE_IN_EASE_OUT);
	radius.setRepeatType(AnimRepeat::LOOP_BACK_AND_FORTH_N_TIMES);
	radius.setDuration(15);
	radius.animateTo(0.6);
	radius.setRepeatTimes(1);

}


void StripeCubes::update()
{
	deltatime = lasttime - ofGetElapsedTimef();
	lasttime = ofGetElapsedTimef();

	time += deltatime * speed;
	time_stripes += deltatime * (speedStripes);

	float val = 0.0;
	if (out)
		val = 2.3;
	else
		val = 0.5;

	if (radius.hasFinishedAnimating() && fabs(radius.val()-val) > 0.1) {
		if (out) {
			radius.reset(radius.val());
			radius.animateTo(2.3);
		}
		else {
			radius.reset(radius.val());
			radius.animateTo(0.5);
		}
	}

	radius.update(deltatime);


}



void StripeCubes::draw()
{
	shader.begin();
	shader.setUniform1i("fullscreen", 0);
	shader.setUniform1f("time", time_stripes);
	shader.setUniform1f("FREQUENCE", 5);
	shader.setUniform1f("TILT", tiltStripes);
	shader.setUniform1f("THIKNESS", thikStripes);
	shader.setUniform1f("SMOOTHNESS", 0.01);
	shader.end();

	render();
	//fbo.draw(0,0);
}

void StripeCubes::setCubes(int count)
{
	for (int i = 0; i < count; i++) {
		boxes.push_back(ofBoxPrimitive(0.6, 0.6, 0.6));
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
	
	ofRotate(time * 10);
	for (int i = 0; i < boxes.size(); i++) {
		
		ofRotate(75);
		ofTranslate(radius.val(), sinf(time + i * 3)*0.25, cosf((time - i * 2) / 2 + 5)*.7);
		boxes[i].draw();
		ofTranslate(-radius.val(), -sinf(time+i*3)*0.25, -cosf((time - i*2) / 2 + 5)*.7);
	}
	ofTranslate(0.5, 0, 0);

}

void StripeCubes::render()
{
	//fbo.begin();
	glEnable(GL_DEPTH_TEST);
	//ofClear(0, 0, 0, 255);
	

	translateMidFlipScale();
	ofScale(1.5, 1.5, 1.5);

	shader.begin();


	rotateBoxes();

	drawBoxes();

	shader.end();
	glDisable(GL_DEPTH_TEST);
	//fbo.end();
}

