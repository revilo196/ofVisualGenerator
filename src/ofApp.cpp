#include "ofApp.h"
#include "VjObject.h"


//--------------------------------------------------------------
void ofApp::setup(){
	texture.setup(1024, 768);
//	overlay.setup(1024, 768);

	gui.setup(texture.getParameterGroup());

}

//--------------------------------------------------------------
void ofApp::update(){

	texture.update();
	//overlay.setTextureIn(texture.getTextureRef());


	//overlay.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
	texture.draw(0, 0);

	gui.draw();
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
