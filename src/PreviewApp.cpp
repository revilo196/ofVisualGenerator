/**
 * @file PreviewApp.cpp
 * @author PreviewApp code
 * @brief 
 * @version 0.1
 * @date 2020-06-26
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "PreviewApp.h"

/**
 * @brief setup the PreviewApp
 * allocate the FBO's
 */
void PreviewApp::setup()
{
	settings.loadFile("settings.xml");
	const int width = settings.getValue("settings:render:width", 1920);
	const int height = settings.getValue("settings:render:height", 1080);
}

/**
 * @brief upadte the window
 * 
 */
void PreviewApp::update()
{
	//Unsued
}

/**
 * @brief draw the diffrent preview FBO's
 * 
 */
void PreviewApp::draw()
{
	ofClear(0, 0, 0, 0);

	for (size_t i = 0; i < layers.size(); i++)
	{
		layers[i].draw(configs[i].offsetX, configs[i].offsetY, configs[i].width, configs[i].height);
	}
}

void PreviewApp::exit()
{
}

/**
 * @brief add a Preview FBO to the preview window
 * 
 * @param lay ofFbo to add to the preview
 * @param conf preview size an position in the window
 */
void PreviewApp::addLayer(ofFbo lay, PreviewConfig conf)
{
	layers.push_back(lay);
	configs.push_back(conf);
}
