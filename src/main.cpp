#include "ofMain.h"
#include "ofApp.h"

#include "glut.h"

//int win_h;
//int other_win_h;

//void changeToOtherWindow() {
//	glutSetWindow(other_win_h);  // have to tell glut which window you are rendering  
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//}
//
//void returnFromOtherWindow() {
//	glutSwapBuffers();
//	glutSetWindow(win_h);
//}

//========================================================================
int main( ){

	ofGLFWWindowSettings settings;
	settings.setGLVersion(4, 5);
	settings.width = 1024;
	settings.height = 769;
	settings.setPosition(ofVec2f(300, 0));
	auto win_h = ofCreateWindow(settings);		

	settings.width = 300;
	settings.height = 300;
	settings.setPosition(ofVec2f(0, 0));
	auto other_win_h = ofCreateWindow(settings);

	auto mainApp = make_shared<ofApp>();
	//auto mainApp2 = make_shared<ofApp>();


	ofRunApp(win_h, mainApp);
	//ofRunApp(other_win_h, mainApp2);
	ofRunMainLoop();
}
