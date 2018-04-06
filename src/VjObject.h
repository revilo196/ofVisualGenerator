#pragma once
#include "ofMain.h"

class VjObject
{
public:

	explicit VjObject(string name = "VjObject");
	~VjObject();

	void addParameter(ofAbstractParameter &parm);
	ofParameterGroup getParameterGroup();
	void setName(string name);
	string getName();

private:
	explicit VjObject();
	ofParameterGroup parameters;
	ofParameter<string> nameParameter;
};

