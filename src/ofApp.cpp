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
	layer6 = mng.createLayer<StripeCubes>(0.2);
	layer7 = mng.createLayer<WaveMeshTexture>(0.2);
	layer8 = mng.createLayer<WaveMeshAdvTex>(0.2);

	//layer.setup(ofGetWidth(),ofGetHeight());
	gui.setup(layer8->getParameterGroup());
	//layer.setGui(&gui);


}

//--------------------------------------------------------------
void ofApp::update(){

	mng.update();
	ofSetWindowTitle(ofToString(ofGetFrameRate(), 2));
	layer8->moveFront();
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofEnableAlphaBlending();
	mng.draw();



	//changeToOtherWindow();
	gui.draw();
	//returnFromOtherWindow();
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


//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
