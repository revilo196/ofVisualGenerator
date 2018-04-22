#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){


	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(0);

	mng.setup();

	layer1 = mng.createLayer<CircleGrow>(.2);
	layer2 = mng.createLayer<ParticleGrowTexture>(0.2);
	layer3 = mng.createLayer<ParticleSystemTexture>(0.2);
	layer4 = mng.createLayer<StripeSpiral>(0.2);
	layer5 = mng.createLayer<SphereGrow>(0.2);
	layer5->setSound(&sound);
	layer6 = mng.createLayer<StripeCubes>(0.2);
	layer7 = mng.createLayer<WaveMeshTexture>(0.2);
	layer8 = mng.createLayer<WaveMeshAdvTex>(0.2);

	layers.push_back(layer1);
	layers.push_back(layer2);
	layers.push_back(layer3);
	layers.push_back(layer4);
	layers.push_back(layer5);
	layers.push_back(layer6);
	layers.push_back(layer7);
	layers.push_back(layer8);

	layerConfigs.push_back(layer1);
	layerConfigs.push_back(layer2);
	layerConfigs.push_back(layer3);
	layerConfigs.push_back(layer4);
	layerConfigs.push_back(layer5);
	layerConfigs.push_back(layer6);
	layerConfigs.push_back(layer7);
	layerConfigs.push_back(layer8);

	gui.setup();

	allGroup.setName("all");
	int i = 0;
	for each (VjObject * var in layerConfigs)
	{
		auto config = new ofxPanel();

		ofParameterGroup parameters = var->getParameterGroup();
		parameters.setName("Layer-" + ofToString(i));
		config->setup(parameters, var->getName() + ".xml");
		allGroup.add(parameters);
		guis.push_back(config);
		currentConfig = config;


		auto btn = new ofxButton();
		btn->addListener(this, &ofApp::buttonPressed);
		btn->setup("Layer-" + ofToString(i));
		gui.add(btn);
		buttons.push_back(btn);
		i++;
	}

	sync.setup(allGroup, 6666, "192.168.105.58", 6667);
	sound.setup();
}

//--------------------------------------------------------------
void ofApp::update(){

	mng.update();
	ofSetWindowTitle(ofToString(ofGetFrameRate(), 2));
	layer8->moveFront();
	sync.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofEnableAlphaBlending();
	mng.draw();


	gui.draw();
	currentConfig->draw();

	vector<float> db = sound.getDB();

	for (int i = 0; i < db.size(); i++) {
		float x = (float)i / ( (float)db.size());

		float h = db[i]*10;

		ofDrawRectangle(x*ofGetWidth() , 0, 30, h);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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

	assert(buttons.size() == layers.size());
	assert(buttons.size() == guis.size());


	for (int i = 0; i < buttons.size(); i++) {
		if (sender == static_cast<void*>(buttons[i])) {
			layers[i]->setAlpha(1.0);
			currentConfig = guis[i];
		}
		else {
			layers[i]->setAlpha(0.0);

		}
	}

}


//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
