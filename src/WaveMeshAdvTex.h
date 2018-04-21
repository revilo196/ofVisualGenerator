#pragma once
#include "WaveMeshTexture.h"
class WaveMeshAdvTex :
	public WaveMeshTexture
{
public:
	explicit WaveMeshAdvTex();
	~WaveMeshAdvTex();

	virtual void setup() override;
	virtual void update() override;

private:
	ofParameter<float> freq;
	ofParameter<float> size;
	ofParameter<float> zToSize;
	ofParameter<float> zToColor;

};

