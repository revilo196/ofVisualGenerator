#include "SoundAnalyzer.h"



SoundAnalyzer::SoundAnalyzer()
{
}


SoundAnalyzer::~SoundAnalyzer()
{
}

void SoundAnalyzer::setup()
{
	vector<ofSoundDevice> devices = soundStream.getDeviceList();

	for (int i = 0; i < devices.size(); i++) {

		ofLog() << devices[i].name;
		for (int j = 0; j < devices[i].sampleRates.size(); j++) {
			ofLog() << devices[i].sampleRates[j];
		}

	}

	soundStream.setDeviceID(7);
	soundStream.setup(0, 1, 48000, bufferSize, 4);
	soundStream.setInput(this);

	audioBuffer.resize(bufferSize * 3);

	power_spectrum.resize((bufferSize * 3 / 2) + 1);
	power_spectrumSmooth.resize((bufferSize * 3 / 2) + 1);

	for (int i = 0; i < power_spectrum.size(); i++) {
		power_spectrum[i] = 0;
		power_spectrumSmooth[i] = 0;
	}

	out.resize((bufferSize * 3 / 2) + 1);
	cfg = kiss_fftr_alloc(bufferSize * 3, 0, NULL, NULL);


	initBands();
	soundStream.start();
}

void SoundAnalyzer::update()
{
}


void SoundAnalyzer::audioIn(ofSoundBuffer & buffer)
{
	rms = buffer.getRMSAmplitude();

	rmsSmooth *= 0.95f; // decay // damping

	if (rmsSmooth < rms) {
		rmsSmooth = rms;  // bump up
	}

	audioBuffer.erase(audioBuffer.begin(), audioBuffer.begin() + buffer.getNumFrames());
	vector<float> input = buffer.getBuffer();
	audioBuffer.insert(audioBuffer.end(), input.begin(), input.end());


	if (cfg != NULL) {
		kiss_fftr(cfg, audioBuffer.data(), out.data());
	}

	for (int i = 0; i < 33; i++) {
		bandSum[i] = 0;
	}

	
	float deltaf = (48000 / (bufferSize * 3));
	for (int i = 0; i < out.size(); i++) {

		power_spectrum[i] = out[i].r * out[i].r;
		power_spectrumSmooth[i] *= 0.95f; // decay // damping
		if (power_spectrumSmooth[i] < power_spectrum[i]) {
			power_spectrumSmooth[i] = power_spectrum[i];  // bump up
		}

		float f = deltaf * i;

		for (int j = 0; j < 33; j++) {

			float gain = sqrt(1.0 / (1 + pow(((f / bands[j].center) - (bands[j].center / f)) * 4.521, 6)));
			bandSum[j] += pow(out[i].r * gain, 2);
		}
	
	}

	for (int j = 0; j < 33; j++) {

		db[j] *= 0.80f; // decay // damping
		float current = sqrt(sqrt(bandSum[j]));
		if (db[j] < current) {
			db[j] = current;  // bump up
		}


	}

}

void SoundAnalyzer::initBands()
{
	bandSum.resize(33);
	bands.resize(33);
	db.resize(33);
	bands[0] = { 11.2f,  12.5f,  14.1f };
	bands[1] = { 14.1f, 16.0f, 17.8f };
	bands[2] = { 17.8f, 20.0f, 22.4f };
	bands[3] = { 22.4f, 25.0f, 28.2f };
	bands[4] = { 28.2f, 31.5f, 35.5f };
	bands[5] = { 35.5f, 40.0f, 44.7f };
	bands[6] = { 44.7f, 50.0f, 56.2f };
	bands[7] = { 56.2f, 63.0f, 70.8f };
	bands[8] = { 70.8f, 80.0f, 89.1f };
	bands[9] = { 89.1f, 100.0f, 112 };
	bands[10] = { 112.0f, 125.0f, 141 };
	bands[11] = { 141.0f, 160.0f, 178 };
	bands[12] = { 178.0f, 200.0f, 224 };
	bands[13] = { 224.0f, 250.0f, 282 };
	bands[14] = { 282.0f, 315.0f, 355 };
	bands[15] = { 355.0f, 400.0f, 447 };
	bands[16] = { 447.0f, 500.0f, 562 };
	bands[17] = { 562.0f, 630.0f, 708 };
	bands[18] = { 708.0f, 800.0f, 891 };
	bands[19] = { 891.0f, 1000.0f, 1122 };
	bands[20] = { 1122.0f, 1250.0f, 1413 };
	bands[21] = { 1413.0f, 1600.0f, 1778 };
	bands[22] = { 1778.0f, 2000.0f, 2239 };
	bands[23] = { 2239.0f, 2500.0f, 2818 };
	bands[24] = { 2818.0f, 3150.0f, 3548 };
	bands[25] = { 3548.0f, 4000.0f, 4467 };
	bands[26] = { 4467.0f, 5000.0f, 5623 };
	bands[27] = { 5623.0f, 6300.0f, 7079 };
	bands[28] = { 7079.0f, 8000.0f, 8913 };
	bands[29] = { 8913.0f, 10000.0f, 11220 };
	bands[30] = { 11220.0f, 12500.0f, 14130 };
	bands[31] = { 14130.0f, 16000.0f, 17780 };
	bands[32] = { 17780.0f, 20000.0f, 22390 };
}


