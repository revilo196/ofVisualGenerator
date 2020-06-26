#pragma once
/**
 * @file SongBeamer.h
 * @author Oliver Walter
 * @brief Songbeamer module for mixing the the songbeamer output into this Stream
 * @version 0.1
 * @date 2020-06-26
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "ofBaseTypes.h"
#include "VjObject.h"

/**
 * @brief SongBeamer Module for mixing the the songbeamer output into this Stream
 * 
 * this is used to overlay the songbeamer 
 * 
 */
class SongBeamer :  public ofBaseUpdates, public VjObject
{
private:
    ofVideoGrabber videoIn; // Video Input
    ofFbo sbEffectOut;      // effect output with blank spots for text from SB 
    ofFbo songOverlay;      // the overlay to remove Mask  for the text
    ofShader yExBlur;       // Blur filter to generate Mask  
	ofShader xExBlur;       // Blur filter to generate Mask 
	ofShader sbmix;            
	ofShader sbAdd;
    ofFbo xEx;
	ofFbo yEx;
	ofFbo xExB;
	ofFbo yExB;
    ofPlanePrimitive fullQuad;

    //Parameter
    ofParameter<bool> fullSong;
	ofParameter<bool> blkSong;
    ofParameter<float> songFade;

    //use the video in to genreate the overlay
    void songBeamerInputRender();

public:
    SongBeamer(string name);
    ~SongBeamer() {};
    void setup(int vid_id, int width, int height);
    void update();
    void draw(ofFbo effectLayer);
    void videoSettings() {videoIn.videoSettings();};
   
};
