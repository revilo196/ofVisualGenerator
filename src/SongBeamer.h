/**
 * @file SongBeamer.h
 * @author Oliver Walter
 * @brief 
 * @version 0.1
 * @date 2020-06-26
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "ofBaseTypes.h"
#include "VjObject.h"

class SongBeamer :  public ofBaseUpdates, public VjObject
{
private:
    ofVideoGrabber videoIn;
    ofFbo sbEffectOut;
    ofFbo songOverlay;
    ofShader yExBlur;
	ofShader xExBlur;
	ofShader sbmix;
	ofShader sbAdd;
    ofFbo xEx;
	ofFbo yEx;
	ofFbo xExB;
	ofFbo yExB;
    ofPlanePrimitive fullQuad;
    ofParameter<bool> fullSong;
	ofParameter<bool> blkSong;
    ofParameter<float> songFade;

    void songBeamerInputRender();

public:
    SongBeamer(string name);
    ~SongBeamer() {};
    void setup(int vid_id, int width, int height);
    void update();
    void draw(ofFbo effectLayer);
    void videoSettings() {videoIn.videoSettings();};
   
};




/*		
        songOverlay.allocate(width, height);
		sbEffectOut.allocate(width, height);
		xEx.allocate(width, height);
		yEx.allocate(width, height);
		xExB.allocate(width, height);
		yExB.allocate(width, height);
		yExBlur.load("shader.vert", "blurYextrem.frag");
		xExBlur.load("shader.vert", "blurXextrem.frag");
		sbmix.load("shader.vert", "blend.frag");
		sbAdd.load("shader.vert", "songadd.frag");*/