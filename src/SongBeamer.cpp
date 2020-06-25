/**
 * @file SongBeamer.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-06-26
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "SongBeamer.h"

SongBeamer::SongBeamer(string name = "SongBeamer"): VjObject(name) {
    addParameter(fullSong.set("only songbeamer",false), false);
    addParameter(blkSong.set("block songbeamer", false), false);
    addParameter(songFade.set("fade songbeamer", 1.0f, 0.0f, 1.0f), false);
}

void SongBeamer::setup(int vid_id, int width, int height) {
    	videoIn.setVerbose(true);
		videoIn.setDeviceID(vid_id);
		videoIn.setUseTexture(true);
		videoIn.setDesiredFrameRate(24);
		videoIn.setPixelFormat(ofPixelFormat::OF_PIXELS_UYVY);
		videoIn.videoSettings();
		videoIn.setup(width, height);
		videoIn.bind();

		songOverlay.allocate(width, height);
		sbEffectOut.allocate(width, height);
		xEx.allocate(width, height);
		yEx.allocate(width, height);
		xExB.allocate(width, height);
		yExB.allocate(width, height);
		yExBlur.load("shader.vert", "blurYextrem.frag");
		xExBlur.load("shader.vert", "blurXextrem.frag");
		sbmix.load("shader.vert", "blend.frag");
		sbAdd.load("shader.vert", "songadd.frag");

        fullQuad.set(width, height);
	    fullQuad.setPosition(width/2, height/2, 0);
	    fullQuad.setResolution(2, 2 );
}

void SongBeamer::update() {
    videoIn.update();
}

void SongBeamer::draw(ofFbo effectLayer) {

    if(fullSong) {
       videoIn.draw(0, 0, ofGetWidth(), ofGetHeight()); #
       return;
    }

    if(blkSong) {
        effectLayer.draw(0, 0);
        return;
    }

    songBeamerInputRender();
    sbEffectOut.begin();
    ofClear(0, 0);

    //------------- mix songOverlay and effectLayer to remove the backgroud 
    sbmix.begin();
    sbmix.setUniformTexture("mtex0", songOverlay.getTexture(), 1);
    sbmix.setUniformTexture("mtex1", effectLayer.getTexture(), 2);
    sbmix.setUniform1i("mode", 1);
    sbmix.setUniform1f("faderA", 1);
    sbmix.setUniform1f("faderB", 1);
    sbmix.setUniform1i("invertA", 1);
    sbmix.setUniform1i("invertB", 0);
    sbmix.setUniform1f("submodeA", -1);
    sbmix.setUniform1i("tcd", 1);
    sbmix.setUniform1i("width", ofGetWidth());
    sbmix.setUniform1i("height", ofGetHeight());
    fullQuad.draw();
    sbmix.end();
    sbEffectOut.end();

    // draw the mixed backgroud together with the videoInput
    sbmix.begin();
    sbmix.setUniformTexture("mtex0", sbEffectOut.getTexture(), 1);
    sbmix.setUniformTexture("mtex1", videoIn.getTexture(), 2);
    sbmix.setUniform1i("mode", 0);
    sbmix.setUniform1f("faderA", 1 - songFade);
    sbmix.setUniform1f("faderB", 1 - songFade);
    sbmix.setUniform1i("invertA", 0);
    sbmix.setUniform1i("invertB", 0);
    sbmix.setUniform1i("tcd", 1);
    sbmix.setUniform1i("width", ofGetWidth());
    sbmix.setUniform1i("height", ofGetHeight());


    fullQuad.draw();
    sbmix.end();
   
}

void SongBeamer::songBeamerInputRender()
{
	xEx.begin();
	ofClear(0, 0);
	xExBlur.begin();
	xExBlur.setUniform1f("blurAmnt", 1);
	xExBlur.setUniform1f("glowAmnt", 10);
	xExBlur.setUniformTexture("tex0", videoIn.getTexture(), 1);
	xExBlur.setUniform2f("format", videoIn.getWidth(), videoIn.getHeight());
	fullQuad.draw();
	xExBlur.end();
	xEx.end();

	xExB.begin();
	ofClear(0, 0);
	yExBlur.begin();
	yExBlur.setUniform1f("blurAmnt", 1);
	yExBlur.setUniform1f("glowAmnt", 10);
	yExBlur.setUniformTexture("tex0", xEx.getTexture(), 1);
	yExBlur.setUniform2f("format", xEx.getWidth(), xEx.getHeight());
	fullQuad.draw();
	yExBlur.end();
	xExB.end();


	xEx.begin();
	ofClear(0, 0);
	xExBlur.begin();
	xExBlur.setUniform1f("blurAmnt", 1);
	xExBlur.setUniform1f("glowAmnt", 10);
	xExBlur.setUniformTexture("tex0", xExB.getTexture(), 1);
	xExBlur.setUniform2f("format", xExB.getWidth(), xExB.getHeight());
	fullQuad.draw();
	xExBlur.end();
	xEx.end();

	xExB.begin();
	ofClear(0, 0);
	yExBlur.begin();
	yExBlur.setUniform1f("blurAmnt", 1);
	yExBlur.setUniform1f("glowAmnt", 10);
	yExBlur.setUniformTexture("tex0", xEx.getTexture(), 1);
	yExBlur.setUniform2f("format", xEx.getWidth(), xEx.getHeight());
	fullQuad.draw();
	yExBlur.end();
	xExB.end();

	//copy
	yExB.begin();
	xExB.draw(0, 0);
	yExB.end();


	for (int i = 5; i > 0; i--)
	{
		xEx.begin();
		ofClear(0, 0);
		xExBlur.begin();
		xExBlur.setUniform1f("blurAmnt", i * 10);
		xExBlur.setUniform1f("glowAmnt", 2);
		xExBlur.setUniformTexture("tex0", xExB.getTexture(), 1);
		xExBlur.setUniform2f("format", xExB.getWidth(), xExB.getHeight());
		fullQuad.draw();
		xExBlur.end();
		xEx.end();

		yEx.begin();
		ofClear(0, 0);
		yExBlur.begin();
		yExBlur.setUniform1f("blurAmnt", i * 10);
		yExBlur.setUniform1f("glowAmnt", 2);
		yExBlur.setUniformTexture("tex0", yExB.getTexture(), 1);
		yExBlur.setUniform2f("format", yExB.getWidth(), yExB.getHeight());
		fullQuad.draw();
		yExBlur.end();
		yEx.end();

		xExB.begin();
		ofClear(0, 0);
		xExBlur.begin();
		xExBlur.setUniform1f("blurAmnt", i * 5);
		xExBlur.setUniform1f("glowAmnt", 2);
		xExBlur.setUniformTexture("tex0", xEx.getTexture(), 1);
		xExBlur.setUniform2f("format", xEx.getWidth(), xEx.getHeight());
		fullQuad.draw();
		xExBlur.end();
		xExB.end();

		yExB.begin();
		ofClear(0, 0);
		yExBlur.begin();
		yExBlur.setUniform1f("blurAmnt", i * 10);
		yExBlur.setUniform1f("glowAmnt", 2);
		yExBlur.setUniformTexture("tex0", yEx.getTexture(), 1);
		yExBlur.setUniform2f("format", yEx.getWidth(), yEx.getHeight());
		fullQuad.draw();
		yExBlur.end();
		yExB.end();

	}

	songOverlay.begin();
	sbmix.begin();

	sbmix.setUniformTexture("mtex0", yEx.getTexture(), 1);
	sbmix.setUniformTexture("mtex1", xEx.getTexture(), 2);
	sbmix.setUniform1i("mode", 1);
	sbmix.setUniform1f("faderA", 1);
	sbmix.setUniform1f("faderB", 1);
	sbmix.setUniform1i("invertA", 0);
	sbmix.setUniform1i("invertB", 0);
	//shader.setUniform1i("width", width);
	//shader.setUniform1i("height", height);
	sbmix.setUniform1i("submodeA", -1);
	sbmix.setUniform1i("submodeB", 0);

	sbmix.setUniform1i("tcd", 1);
	sbmix.setUniform1i("width", ofGetWidth());
	sbmix.setUniform1i("height", ofGetHeight());


	fullQuad.draw();

	sbmix.end();
	songOverlay.end();
}