#include "ofMain.h"
#include "ofApp.h"
#include "PreviewApp.h"

#include "ofxXmlSettings.h"


const char config[] = "<settings><osc><ip>192.168.105.33</ip><port_in>6666</port_in><port_out>6667</port_out ></osc><render><width>1920</width><height>1080 </height ></render><audioInID>5 </audioInID ><vidioInID>0</vidioInID><artnetEnable>1 </artnetEnable ><artnetPort>1 </artnetPort></settings>";


//========================================================================
int main(int argc, char** árgv) {


	ofxXmlSettings xmlsettings;

	if (!xmlsettings.loadFile("settings.xml")) {
		xmlsettings.loadFromBuffer(config);
		xmlsettings.saveFile("settings.xml");
	}


	int width = xmlsettings.getValue("settings:render:width", 1920);
	int height = xmlsettings.getValue("settings:render:height", 1080);


	ofGLFWWindowSettings settings;
	settings.setGLVersion(4, 1);
	settings.setSize(width, height);
	settings.setPosition(ofVec2f(50, 50));
	settings.windowMode = OF_WINDOW;
	settings.monitor = 1;
	shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);

	settings.windowMode = OF_WINDOW;
	settings.monitor = 1;
	settings.setSize(width, height);
	settings.setPosition(ofVec2f(0, 50));
	settings.shareContextWith = mainWindow;
	shared_ptr<ofAppBaseWindow> other_win_h = ofCreateWindow(settings);
	//other_win_h->setVerticalSync(false);

	shared_ptr<ofApp> mainApp(new ofApp);
	shared_ptr<PreviewApp> preview_app(new PreviewApp);
	
	mainApp->preview = preview_app;

	ofRunApp(mainWindow, mainApp);
	ofRunApp(other_win_h, preview_app);
	ofRunMainLoop();
}
