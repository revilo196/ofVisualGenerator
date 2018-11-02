#include "ofMain.h"
#include "ofApp.h"

#include "glut.h"


//========================================================================
int main( ){

	ofGLFWWindowSettings settings;
	settings.setGLVersion(4, 5);
	settings.width = 1920;
	settings.height = 1080;
	settings.setPosition(ofVec2f(50, 50));
	settings.windowMode = OF_WINDOW;
	settings.monitor = 1;
	shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);

	settings.windowMode = OF_WINDOW;
	settings.monitor = 0;
	settings.width = 1920;
	settings.height = 1080;
	settings.setPosition(ofVec2f(0, 50));
	settings.shareContextWith = mainWindow;
	shared_ptr<ofAppBaseWindow> other_win_h = ofCreateWindow(settings);
	other_win_h->setVerticalSync(false);

	shared_ptr<ofApp> mainApp(new ofApp);

	ofAddListener(other_win_h->events().draw, mainApp.get(), &ofApp::drawPre);


	ofRunApp(mainWindow, mainApp);
	//ofRunApp(other_win_h, mainApp2);
	ofRunMainLoop();
}
