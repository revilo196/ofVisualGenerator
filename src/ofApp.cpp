#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup() {

	settings.loadFile("settings.xml");

	ofSetFrameRate(25);
	ofSetVerticalSync(false);
	ofBackground(0);

	const int width = settings.getValue("settings:render:width", 1920);
	const int height = settings.getValue("settings:render:height", 1080);
	
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

	a12.setup(&mgl1, &mgl2, width, height);
	b34.setup(&mgl3, &mgl4, width, height);
	
	outAB.setup(&a12, &b34, width, height);


	allGroup.add(a12.all);
	allGroup.add(b34.all);
	allGroup.add(outAB.all);


	preFbo.allocate(width, height);
	preFboOut.allocate(width, height);
	effectLayer.allocate(width, height);

	gui.setup(allGroup);


	fullQuad.set(width, height);
	fullQuad.setPosition(width/2, height/2, 0);
	fullQuad.setResolution(2, 2);


	sync.setup(allGroup, settings.getValue("settings:osc:port_in", 6666 ), settings.getValue("settings:osc:ip", "192.168.1.1"), settings.getValue("settings:osc:port_out", 6667));


	#ifdef NDI_OUT
		strcpy_s(senderName, 256, "Openframeworks NDI Sender"); // Set the sender name
		cout << ndiSender.GetNDIversion() << " (http://ndi.tv/)" << endl;
		// Create an RGBA fbo for collection of data
		ndiFbo.allocate(width, height, GL_RGBA);
		// Optionally set fbo readback using OpenGL pixel buffers
		ndiSender.SetReadback(); // Change to false to compare
		// Optionally set NDI asynchronous sending
		// instead of clocked at the specified frame rate (60fps default)
		ndiSender.SetAsync();
		ndiSender.CreateSender(senderName, width, height);
		cout << "Created NDI sender [" << senderName << "] (" << width << "x" << height << ")" << endl;
	#endif // NDI_OUT

	#ifdef SOUND
		soundID = settings.getValue("settings:audioInID", 1);
		if (soundID >= 0) {
			VjObject::rms = &this->rms;
			sound.setup();
		}
	#endif // SOUND

	#ifdef SONGBEAMER
		videoID = settings.getValue("settings:vidioInID", 1);
		if (videoID > 0) {
			sb_mix.setup(videoID, width, height);
			allGroup.add(sb_mix.getParameterGroup());
		}
	#endif // SONGBEAMER

	#ifdef ARTNET_IN
			if (artnet > 0) {
				allGroup.add(dimm.set("artD", 0, 0, 255));
				allGroup.add(stro.set("artS", 0, 0, 255));
				allGroup.add(colR.set("artR", 0, 0, 255));
				allGroup.add(colG.set("artG", 0, 0, 255));
				allGroup.add(colB.set("artB", 0, 0, 255));

				allGroup.add(artL1.set("artL1", false));
				allGroup.add(artL2.set("artL2", false));
				allGroup.add(artL3.set("artL3", false));
				allGroup.add(artL4.set("artL4", false));
			}
	#endif // ARTNET
}

//--------------------------------------------------------------
void ofApp::update(){

	ofSetWindowTitle(ofToString(ofGetFrameRate(), 2));

	sync.update();


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


	#ifdef SONGBEAMER
		if (videoID >= 0) {
			sb_mix.update();
		}
	#endif

	#ifdef SOUND
		if (soundID >= 0) {
			rms = sound.getRMSSmooth();
		}
	#endif // SOUND

	#ifdef ARTNET_IN
		artnet = settings.getValue("settings:artnetPort", 0);
		if (artnet > 0) {
			art();
		}
	#endif // ARTNET
}

//--------------------------------------------------------------
void ofApp::draw(){
	updatePre();

	ofEnableAlphaBlending();

	#ifdef SONGBEAMER
		if (videoID >= 0) {
			sb_mix.draw(effectLayer);
		}
		else {
			effectLayer.draw(0, 0);
		}
	#else
		effectLayer.draw(0, 0);
	#endif

	if(!fullscreen)
		gui.draw();

	#ifdef NDI_OUT
		ndiSender.SendImage(effectLayer);
	#endif
}

void ofApp::drawPreviewLayer(ofxLayer::Layer * layer) {
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		preFbo.begin();
		ofSetColor(255, 255);
		ofClear(0, 0);
		layer->draw();
		preFbo.end();
	}
	glPopAttrib();
}

void ofApp::updatePre()
{

	preFboOut.begin();
	ofClear(0, 0, 0, 0);

	const float scale = 1.2;
	const float xoff = 200;
	const float yoff = 0;
	const float gap = 10;
	const float w = 425 * scale;
	const float h = 240 * scale;


	drawPreviewLayer(&mgl1);
	preFbo.draw(0 + xoff, 0 + yoff, w , h);
	
	drawPreviewLayer(&mgl3);
	preFbo.draw(0 + xoff , h + yoff +gap , w, h);

	drawPreviewLayer(&mgl2);
	preFbo.draw(w + xoff + gap , 0 +yoff, w, h);

	drawPreviewLayer(&mgl4);
	preFbo.draw(w + xoff + gap , h + yoff + gap , w, h);

	drawPreviewLayer(&a12);
	preFbo.draw(w*2 + gap *2 + xoff, 0 + yoff, w, h);

	drawPreviewLayer(&b34);
	preFbo.draw(w * 2 + gap * 2 + xoff, h + yoff + gap, w, h);

	drawPreviewLayer(&outAB);
	preFbo.draw(w + gap * 2 + xoff, h * 2 + yoff + gap*2 , w*1.25, h*1.25);

	preFboOut.end();


}

void ofApp::drawPre(ofEventArgs & args)
{ 
	ofClear(0, 0, 0, 0);

	ofDrawCircle(5, 5, 20);
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

	#ifdef SONGBEAMER
		if (key == 's') {
			sb_mix.videoSettings();
		}
	#endif

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}


//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}


//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

void ofApp::exit() {


#ifdef NDI_OUT
	// The sender must be released 
	// or NDI sender discovery will still find it
	ndiSender.ReleaseSender();
#endif // NDI_OUT

}

#ifdef ARTNET_IN
void ofApp::art()
{

	float time = ofGetElapsedTimef();
	float timfrac = time - (long)time;
	int timefracind = timfrac * 20;

	if (artL1) {
		ofParameterGroup config = allGroup.getGroup("LMG0").getGroup("config");
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
			mix.getInt("invertA") = (timefracind % 2);
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
#endif //ARTNET