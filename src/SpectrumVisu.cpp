/**
 * @file SpectrumVisu.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-06-27
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "SpectrumVisu.h"

#include "SoundAnalyzer.h"

SpectrumVisu::SpectrumVisu() : VjObject("SpectrumVisu") {
    
}


void SpectrumVisu::setup() {

}

void SpectrumVisu::update() {

}

void SpectrumVisu::draw() {
        if(VjObject::sound_connect) {
        auto db = VjObject::sound_connect->getDB();

        for(int i = 0; i < db.size(); i++) {

            ofDrawRectangle(i*20,128, 20,10*db[i]+10);

        }

    }
}