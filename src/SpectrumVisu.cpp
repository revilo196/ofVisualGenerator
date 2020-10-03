/**
 * @file SpectrumVisu.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-06-27
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "SpectrumVisu.h"
#include "SoundAnalyzer.h"

SpectrumVisu::SpectrumVisu() : VjObject("SpectrumVisu") {

	addParameter(speed.set("speed", 1, 0, 2),false);
	addParameter(disort.set("disort", 500, 100, 1000), false);
	addParameter(freq.set("freq", 0.005, 0.000, 0.020), false);
	addParameter(blurXval.set("blurX", 1, 0, 2), false);
	addParameter(blurYval.set("blurY", 1, 0, 2), false);

	addParameter(xoffset.set("xoffset", 0, -1, 1), false);
	addParameter(minheight.set("minheight", 0.03, 0, 0.3), false);
	addParameter(gain.set("gain", 1, 0, 3), false);
	

	addParameter(max_rgb_r.set("max_rgb_r", 0, 0, 1), false);
	addParameter(max_rgb_g.set("max_rgb_g", 0, 0, 1), false);
	addParameter(max_rgb_b.set("max_rgb_b", 1, 0, 1), false);

	addParameter(min_rgb_r.set("min_rgb_r", 1, 0, 1), false);
	addParameter(min_rgb_g.set("min_rgb_g", 0, 0, 1), false);
	addParameter(min_rgb_b.set("min_rgb_b", 0, 0, 1), false);



	runtime = 0.0f;
}


void SpectrumVisu::setup() {
	wave.load("wave.frag");
	blurX.load("xblurX.frag");
	blurY.load("xblurY.frag");
	wave.allocate(VjObject::width, VjObject::height);
	blurX.allocate(VjObject::width, VjObject::height);
	blurY.allocate(VjObject::width, VjObject::height);
	fbo.allocate(VjObject::width, VjObject::height);
}

void SpectrumVisu::update() {
	runtime += ofGetLastFrameTime() * speed;

	ofPushMatrix();
	ofPushStyle();

	ofFloatColor colorA(max_rgb_r, max_rgb_g, max_rgb_b);
	ofFloatColor colorB(min_rgb_r, min_rgb_g, min_rgb_b);
	ofFloatColor colorLerp;
	float dbMax = 50.0f;

	if (VjObject::sound_connect) {
		auto db = VjObject::sound_connect->getDB();
		
		float start = -1.8;
		float width = 3.8 / db.size();
		float height_min = minheight;
		


		fbo.begin();
		ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);
		VjObject::translateMidFlipScale();

		ofClear(0, 0, 0);
		
		for (int i = 0; i < db.size(); i++) {
			float alpha = ofMap(db[i] * gain, 0, dbMax, 0, 1.0, true);

			float hue = ofLerpDegrees(colorA.getHue()*360.0f, colorB.getHue()*360.0f, alpha) / 360.0f;
			if (hue < 0) { hue += 1.0f; }
			float sat = ofLerp(colorA.getSaturation(), colorB.getSaturation(), alpha);
			float bri = ofLerp(colorA.getSaturation(), colorB.getSaturation(), alpha);

			colorLerp.setHsb(hue, sat, bri);

			ofSetColor(colorLerp);
			ofDrawRectangle(start + i * width, xoffset, width*1.01, alpha + height_min);

		}
		fbo.end();



	}
	ofPopStyle();
	ofPopMatrix();

	blurX.setUniformTexture("tex0", fbo.getTexture());
	blurY.setUniformTexture("tex0", blurX.getTexture());

	blurX.setUniform1f("glowAmnt", 0.1);
	blurY.setUniform1f("glowAmnt", 0.1);
	for (int i = 0; i < 10; i++) {
		blurX.setUniform1f("blurAmnt", blurXval* (10 - (i)) * 0.2);
		blurY.setUniform1f("blurAmnt", blurYval * (10 - (i)) * 0.2);
		blurX.render();
		blurY.render();
		if (i == 0) {blurX.setUniformTexture("tex0", blurY.getTexture());}
	}

	wave.setUniform1f("freq", freq);
	wave.setUniform1f("disort", disort);
	wave.setUniform1f("s_time", runtime);


	wave.setUniformTexture("mtex0", blurY.getTexture());
	wave.render();
}

void SpectrumVisu::draw() {

	wave.draw(0, 0);

}