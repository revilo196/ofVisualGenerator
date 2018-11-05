#include "WaveMeshAdvTex.h"



WaveMeshAdvTex::WaveMeshAdvTex() : WaveMeshTexture()
{
	addParameter(freq.set("dot count", 256.0f, 64.0f, 512.0f));
	addParameter(size.set("dot size", 0.1, 0.0, 1.5));
	addParameter(zToSize.set("zToSize", 0.8, 0.0, 1.5));
	addParameter(zToColor.set("zToColor", 0.8, 0.0, 1.5));

	this->setResulution(512);
}


WaveMeshAdvTex::~WaveMeshAdvTex()
{
}

void WaveMeshAdvTex::setup()
{
	WaveMeshTexture::setup();

	this->shader.load("waveMeshAdv.vert", "waveMeshAdv.frag");
	setRenderMode(RenderMode::RM_SURFACE);
}

void WaveMeshAdvTex::update()
{	
	this->updateParms();


	shader.begin();
	shader.setUniform1f("freq", freq);
	shader.setUniform1f("size", size);
	shader.setUniform1f("zToSize", zToSize);
	shader.setUniform1f("zToColor", zToColor);
	shader.end();

	WaveMeshTexture::update();
}
