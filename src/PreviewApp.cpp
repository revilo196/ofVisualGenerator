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

void PreviewApp::update()
{
}


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

void PreviewApp::addLayer(ofFbo lay, PreviewConfig conf)
{
	layers.push_back(lay);
	configs.push_back(conf);
}
