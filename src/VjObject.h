#pragma once
#include "ofMain.h"

class VjObject
{
public:

	explicit VjObject(string name = "VjObject");
	~VjObject();

	void addParameter(ofAbstractParameter &parm);
	ofParameterGroup getParameterGroup();
	void setParameterGroup(ofParameterGroup gp) { parameters = gp; }
	void clearParameter();
	void setName(string name);
	string getName();

	void translateMidFlipScale()  const {
		float cy = ofGetHeight() / 2;
		float cx = ofGetWidth() / 2;
		ofTranslate(cx, cy);
		ofScale(cy, -cy, cy);
	}

protected:
	ofParameterGroup parameters;

private:
	explicit VjObject();
	ofParameter<string> nameParameter;
};


