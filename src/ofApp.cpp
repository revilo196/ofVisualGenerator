#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){


	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(0);
	//ofToggleFullscreen();
	//fullscreen = true;

	const int width = 1920;
	const int height = 1080;

	std::vector<ofVideoDevice> videoList = videoIn.listDevices();

	for (int i = 0; i < videoList.size(); i++) {
		
		ofLogNotice("VideoIn", videoList[i].deviceName + "  " + ofToString(videoList[i].id));
	
	}

	videoIn.setDeviceID(0);
	videoIn.setUseTexture(true);
	videoIn.setDesiredFrameRate(60);
	//videoIn.videoSettings();
	videoIn.setup(width, height);
	videoIn.bind();

	VjObject::rms = &this->rms;

	sound.setup();

	mgl1.setup();
	mgl2.setup();
	mgl3.setup();
	mgl4.setup();



	mgl1.selfInit();
	mgl2.selfInit();
	mgl3.selfInit();
	mgl4.selfInit();


	
	allGroup.add(mgl1.all);
	allGroup.add(mgl2.all);
	allGroup.add(mgl3.all);
	allGroup.add(mgl4.all);


	a12.setup(&mgl1, &mgl2);
	b34.setup(&mgl3, &mgl4);
	
	outAB.setup(&a12, &b34);


	
	allGroup.add(a12.all);

	allGroup.add(b34.all);

	allGroup.add(outAB.all);
	allGroup.add(dimm.set("artD",0, 0,255));
	allGroup.add(stro.set("artS", 0, 0, 255));
	allGroup.add(colR.set("artR", 0, 0, 255));
	allGroup.add(colG.set("artG", 0, 0, 255));
	allGroup.add(colB.set("artB", 0, 0, 255));

	allGroup.add(artL1.set("artL1",false ));
	allGroup.add(artL2.set("artL2", false));
	allGroup.add(artL3.set("artL3", false));
	allGroup.add(artL4.set("artL4", false));

	allGroup.add(fullSong.set("fullSong", false));
	allGroup.add(blkSong.set("blkSong", false));




	preFbo.allocate(width, height);
	preFboOut.allocate(width, height);
	effectLayer.allocate(width, height);
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

	gui.setup(allGroup);


	fullQuad.set(width, height);
	fullQuad.setPosition(width/2, height/2, 0);
	fullQuad.setResolution(2, 2 );

	sync.setup(allGroup, 6666, "10.0.0.197", 6667);

}

//--------------------------------------------------------------
void ofApp::update(){

	rms = sound.getRMSSmooth();
	ofSetWindowTitle(ofToString(ofGetFrameRate(), 2));
	videoIn.update();

	songBeamerInputRender();
	 
	sync.update();

	art();

	mgl1.update();
	mgl2.update();
	mgl3.update();
	mgl4.update();

	a12.update();
	b34.update();

	outAB.update();

	effectLayer.begin();
	ofClear(0, 0);
	outAB.draw();
	effectLayer.end();

	sbEffectOut.begin();
	ofClear(0, 0);

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


	updatePre();


}

//--------------------------------------------------------------
void ofApp::draw(){

	ofEnableAlphaBlending();


	if (!fullSong)
	{

		if (!blkSong) {

			sbmix.begin();
			sbmix.setUniformTexture("mtex0", sbEffectOut.getTexture(), 1);
			sbmix.setUniformTexture("mtex1", videoIn.getTexture(), 2);
			sbmix.setUniform1i("mode", 0);
			sbmix.setUniform1f("faderA", 1);
			sbmix.setUniform1f("faderB", 1);
			sbmix.setUniform1i("invertA", 0);
			sbmix.setUniform1i("invertB", 0);
			sbmix.setUniform1i("tcd", 1);
			sbmix.setUniform1i("width", ofGetWidth());
			sbmix.setUniform1i("height", ofGetHeight());


				fullQuad.draw();
				//ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

				sbmix.end();
			
		}
		else {
			effectLayer.draw(0, 0);
		}

	}
	else {
		videoIn.draw(0, 0, ofGetWidth(), ofGetHeight());
	}

	if(!fullscreen)
		gui.draw();

	vector<float> db = sound.getDB();

}

void ofApp::art()
{	

	float time = ofGetElapsedTimef();
	float timfrac = time - (long)time;
	int timefracind = timfrac * 20 ;

	if (artL1) {
		ofParameterGroup config =  allGroup.getGroup("LMG0").getGroup("config");
		ofParameterGroup num = config.getGroup("0");

		if ((int)num.getFloat("r") != (int)colR || (int)num.getFloat("g") != (int)colG || (int)num.getFloat("b") != (int)colB) {

			num.getFloat("r") = ((float)colR);
			num.getFloat("g") = ((float)colG);
			num.getFloat("b") = ((float)colB);
			num = config.getGroup("1");
			num.getFloat("r") = ((float)colR);
			num.getFloat("g") = ((float)colG);
			num.getFloat("b") = ((float)colB);
			num = config.getGroup("2");
			num.getFloat("r") = ((float)colR);
			num.getFloat("g") = ((float)colG);
			num.getFloat("b") = ((float)colB);

		}
		if (stro > 128) {
			ofParameterGroup mix = allGroup.getGroup("Mixer0");
			mix.getInt("invertA") = (timefracind % 2);
		}

	}
	if (artL2) {
		ofParameterGroup config = allGroup.getGroup("LMG1").getGroup("config");
		ofParameterGroup num = config.getGroup("0");

		if ((int)num.getFloat("r") != (int)colR || (int)num.getFloat("g") != (int)colG || (int)num.getFloat("b") != (int)colB) {

			num.getFloat("r").set((float)colR);
			num.getFloat("g").set((float)colG);
			num.getFloat("b").set((float)colB);
			num = config.getGroup("1");
			num.getFloat("r").set((float)colR);
			num.getFloat("g").set((float)colG);
			num.getFloat("b").set((float)colB);
			num = config.getGroup("2");
			num.getFloat("r").set((float)colR);
			num.getFloat("g").set((float)colG);
			num.getFloat("b").set((float)colB);
		}


		if (stro > 128) {
			ofParameterGroup mix = allGroup.getGroup("Mixer0");
			mix.getInt("invertB") = (timefracind % 2);
		}

	}
	if (artL3) {
		ofParameterGroup config = allGroup.getGroup("LMG2").getGroup("config");
		ofParameterGroup num = config.getGroup("0");

		if ((int)num.getFloat("r") != (int)colR || (int)num.getFloat("g") != (int)colG || (int)num.getFloat("b") != (int)colB) {

			num.getFloat("r").set((float)colR);
			num.getFloat("g").set((float)colG);
			num.getFloat("b").set((float)colB);
			num = config.getGroup("1");
			num.getFloat("r").set((float)colR);
			num.getFloat("g").set((float)colG);
			num.getFloat("b").set((float)colB);
			num = config.getGroup("2");
			num.getFloat("r").set((float)colR);
			num.getFloat("g").set((float)colG);
			num.getFloat("b").set((float)colB);
		}

		if (stro > 128) {
			ofParameterGroup mix = allGroup.getGroup("Mixer1");
			mix.getInt("invertA") = (timefracind % 2) ;
		}
	}
	if (artL4) {
		ofParameterGroup config = allGroup.getGroup("LMG3").getGroup("config");
		ofParameterGroup num = config.getGroup("0");

		if ((int)num.getFloat("r") != (int)colR || (int)num.getFloat("g") != (int)colG || (int)num.getFloat("b") != (int)colB) {

			num.getFloat("r").set((float)colR);
			num.getFloat("g").set((float)colG);
			num.getFloat("b").set((float)colB);
			num = config.getGroup("1");
			num.getFloat("r").set((float)colR);
			num.getFloat("g").set((float)colG);
			num.getFloat("b").set((float)colB);
			num = config.getGroup("2");
			num.getFloat("r").set((float)colR);
			num.getFloat("g").set((float)colG);
			num.getFloat("b").set((float)colB);

		}

		if (stro > 128) {
			ofParameterGroup mix = allGroup.getGroup("Mixer1");
			mix.getInt("invertB") = (timefracind % 2);
		}
	}


}

void ofApp::songBeamerInputRender()
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

void ofApp::updatePre()
{

	preFboOut.begin();
	ofClear(0, 0, 0, 0);

	float scale = 1.2;
	float xoff = 200;
	float yoff = 0;
	float gap = 10;
	float w = 425 * scale;
	float h = 240 * scale;

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		preFbo.begin();

		ofPushStyle();
		//glPushMatrix();


		ofSetColor(255, 255);
		ofClear(0, 0);
		mgl1.draw();

		//glPopMatrix();
		ofPopStyle();

		preFbo.end();
	}
	glPopAttrib();



	preFbo.draw(0 + xoff, 0 + yoff, w , h);
	
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
	preFbo.begin();

	ofPushStyle();
	//glPushMatrix();



	ofSetColor(255, 255);
	ofClear(0, 0);

	mgl3.draw();

	//glPopMatrix();
	ofPopStyle();

	preFbo.end();
	}
	glPopAttrib();

	preFbo.draw(0 + xoff , h + yoff +gap , w, h);


	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
	preFbo.begin();

	ofPushStyle();
	//glPushMatrix();



	ofSetColor(255, 255);
	ofClear(0, 0);

	mgl2.draw();

	//glPopMatrix();
	ofPopStyle();

	preFbo.end();
	}
	glPopAttrib();

	preFbo.draw(w + xoff + gap , 0 +yoff, w, h);


	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
	preFbo.begin();

	ofPushStyle();
	//glPushMatrix();



	ofSetColor(255, 255);
	ofClear(0, 0);

	mgl4.draw();

	//glPopMatrix();
	ofPopStyle();

	preFbo.end();
	}
	glPopAttrib();

	preFbo.draw(w + xoff + gap , h + yoff + gap , w, h);


	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		preFbo.begin();

		ofPushStyle();
		//glPushMatrix();



		ofSetColor(255, 255);
		ofClear(0, 0);

		a12.draw();

		//glPopMatrix();
		ofPopStyle();

		preFbo.end();
	}
	glPopAttrib();

	preFbo.draw(w*2 + gap *2 + xoff, 0 + yoff, w, h);

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		preFbo.begin();

		ofPushStyle();
		//glPushMatrix();



		ofSetColor(255, 255);
		ofClear(0, 0);

		b34.draw();

		//
		ofPopStyle();

		preFbo.end();
	}
	glPopAttrib();

	preFbo.draw(w * 2 + gap * 2 + xoff, h + yoff + gap, w, h);


	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		preFbo.begin();

		ofPushStyle();
		//glPushMatrix();



		ofSetColor(255, 255);
		ofClear(0, 0);

		outAB.draw();

		//
		ofPopStyle();

		preFbo.end();
	}
	glPopAttrib();

	preFbo.draw(w + gap * 2 + xoff, h * 2 + yoff + gap*2 , w*1.25, h*1.25);

	preFboOut.end();


}

void ofApp::drawPre(ofEventArgs & args)
{ 
	ofClear(0, 0, 0, 0);
	glPushMatrix();

	ofTranslate(1920, 1080, 0);
	ofRotate(180);

	preFboOut.draw(0, 0);
	glPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'f') {
		ofToggleFullscreen();
		fullscreen = !fullscreen;
	}


	if (key == 's') {
		videoIn.videoSettings();
	}

	

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}



void ofApp::buttonPressed(const void * sender)
{


}


//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
