#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup() {

	settings.loadFile("settings.xml");

	ofSetFrameRate(settings.getValue("settings:render:framerate", 25));
	ofSetVerticalSync(false);
	ofBackground(0);

	const int width = settings.getValue("settings:render:width", 1920);
	const int height = settings.getValue("settings:render:height", 1080);
	VjObject::width = width;
	VjObject::height = height;

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
	wa12.setup(&a12, width, height);
	b34.setup(&mgl3, &mgl4, width, height);
	outAB.setup(&a12, &b34, width, height);

	wa12.setup(&a12, width, height);
	wb34.setup(&b34, width, height);
	effectEndMixer.setup(&outAB, width, height);

	allGroup.add(a12.all);
	allGroup.add(b34.all);
	allGroup.add(outAB.all);


	gui.setup(allGroup);


	fullQuad.set(width, height);
	fullQuad.setPosition(width/2, height/2, 0);
	fullQuad.setResolution(2, 2);


	sync.setup(allGroup, settings.getValue("settings:osc:port_in", 6666 ), settings.getValue("settings:osc:ip", "192.168.1.1"), settings.getValue("settings:osc:port_out", 6667));

	const int xoff = 200;
	const int yoff = 0;
	const int gap = 10;
	const int w = 425 * 1.2;
	const int h = 240 * 1.2;
	
	preview->addLayer(mgl1.getFrameBuffer(), { 0 + xoff, 0 + yoff, w,h });
	preview->addLayer(mgl3.getFrameBuffer(), { 0 + xoff , h + yoff + gap, w,h });
	preview->addLayer(mgl2.getFrameBuffer(), { w + xoff + gap , 0 + yoff, w,h });
	preview->addLayer(mgl4.getFrameBuffer(), { w + xoff + gap , h + yoff + gap, w,h });
	preview->addLayer(wa12.wrapper, { w * 2 + gap * 2 + xoff, 0 + yoff, w,h });
	preview->addLayer(wb34.wrapper, { w * 2 + gap * 2 + xoff, h + yoff + gap, w,h });
	preview->addLayer(effectEndMixer.wrapper, { w + gap * 2 + xoff, h * 2 + yoff + gap * 2 , w+w/4, h+h/4 });
	

	#ifdef NDI_OUT
		auto ndiname = settings.getValue("settings:ndi:name", "Openframeworks NDI Sender");
		strcpy_s(senderName, 256, ndiname.c_str()); // Set the sender name
		cout << ndiSender.GetNDIversion() << " (http://ndi.tv/)" << endl;
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

	wa12.update();
	wb34.update();
	effectEndMixer.update();


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
	ofFbo effectLayer = effectEndMixer.wrapper;

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