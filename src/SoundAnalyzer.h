#pragma once

#include "ofSoundStream.h"
#include "ofSoundBuffer.h"
#include "kiss_fftr.h"
#include "ofThread.h"
#include "ofxXmlSettings.h"
struct Band {
	float low;
	float center;
	float high;
};

class SoundAnalyzer : public ofBaseSoundInput
{
public:
	SoundAnalyzer();
	~SoundAnalyzer();

	void setup(int devID);
	void update();

	void initBands();

	void audioIn(ofSoundBuffer &buffer);

	float getRMS() const { return rms; }
	float getRMSSmooth() const { return rmsSmooth; }
	vector<float> getDB() const { return db; }
	vector<float> getSpectrum() const { return power_spectrum; }
	vector<float> getSpectrumSmooth() const { return power_spectrumSmooth; }


private:
	ofxXmlSettings settings;
	ofSoundStream soundStream;
	const int bufferSize = 2048;

	float current =0;
	float rms =0;
	float rmsSmooth=0;
	vector<float> audioBuffer;
	vector<float> power_spectrum;
	vector<float> power_spectrumSmooth;

	vector<kiss_fft_cpx> out;
	kiss_fftr_cfg cfg;

	vector<Band> bands;
	vector<float> bandSum;
	vector<float> db;
};


