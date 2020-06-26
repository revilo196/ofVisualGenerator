#pragma once
#include "ofMain.h"

class VjObject
{
public:
	const static float * rms;
	static int width;
	static int height;

	explicit VjObject(string name = "VjObject");
	~VjObject();

	void addParameter(ofAbstractParameter &parm, bool addRMS = true);
	ofParameterGroup getParameterGroup();

	void setParameterGroup(ofParameterGroup gp) { parameters = gp; }

	void setName(string name);
	string getName();

	virtual void updateParms();
	//virtual void setRMS(float * rmsptr) { this->rms = rmsptr; }

	static void translateMidFlipScale() {
		float cy = height / 2;
		float cx = width / 2;
		ofTranslate(cx, cy);
		ofScale(cy, -cy, cy);
	}

protected:
	ofParameterGroup parameters;

private:
	explicit VjObject();
	ofParameter<string> nameParameter;

	vector<ofParameter<float>> mod;
	vector<ofParameter<bool>> act;
	ofParameterGroup modg1;

};


