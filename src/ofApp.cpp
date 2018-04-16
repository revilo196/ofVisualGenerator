#include "ofApp.h"
#include "VjObject.h"
#include "ParticleGrowTexture.h"

//--------------------------------------------------------------
void ofApp::setup(){


	textures.push_back(new StripeSpiral("Layer01a"));
	textures.push_back(new ParticleGrowTexture("Layer01a"));
	textures.push_back(new CircleGrow("Layer01b"));
	textures.push_back(new SimpleDots("Layer01c"));
	textures.push_back(new SimpleStripes("Layer01d"));
	textures.push_back(new SphereGrow("Layer01e"));
	textures.push_back(new StripeCubes("Layer01f"));
	textures.push_back(new WaveMeshAdvTex("Layer01g"));
	textures.push_back(new WaveMeshTexture("Layer01h"));


	for(int i = 0; i < textures.size(); i++) {
		textures[i]->setup(1024, 768);
	}
	choose = 1;

//	texture.setup(1024, 768);
//	overlay.setup(1024, 768);
	main.add(choose.set("choose", 1, 0, 7));
	lastchoose = 1;

	gui2.setup(main);

	gui.setup(textures[choose]->getParameterGroup());

	//gui.setup(texture.getParameterGroup());


}

//--------------------------------------------------------------
void ofApp::update(){

	if(choose != lastchoose) {
		lastchoose= choose;
		gui.setup(textures[choose]->getParameterGroup());

	}

	textures[choose]->update();
	//texture.update();
	//overlay.setTextureIn(texture.getTextureRef());


	//overlay.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
	textures[choose]->draw(0, 0);

	//texture.draw(0,0);
	gui.draw();
	gui2.draw();
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
