#include "WaveMeshTexture.h"
#include "ofFbo.h"


WaveMeshTexture::WaveMeshTexture( string name) : TextureGen(name)
{
	addParameter(renderMode.set("renderMode", RenderMode::RM_WIRE, RenderMode::RM_WIRE, RenderMode::RM_SURFACE));
	addParameter(speedFront.set("speedFront", 0.5f, -1.0f, 1.0f));
	addParameter(speedLeft.set("speedLeft", 0.5f, -1.0f, 1.0f));
	addParameter(speedZ.set("speedZ", 0.5f, 0.0f, 10.0f));
	addParameter(amplitude.set("amplidude", 128.0f, 0.0f, 512.0f));
	addParameter(wire.set("wire", true));
	addParameter(rotateZ.set("rotateZ", 3.0f, 0.0f, 30.0f));
	this->res = 256;

}

WaveMeshTexture::~WaveMeshTexture()
{
}

void WaveMeshTexture::setResulution(int res)
{
	this->res = res;
}

void WaveMeshTexture::setup(float width, float height)
{
	TextureGen::setup(width, height);

	fbo.allocate(width, height);

	shader.load("waveMeshTexture");

	plane.set(width * 2, height * 4);
	plane.setPosition(0, 0, 0);
	plane.setResolution(res, res * 2);
}

ofTexture & WaveMeshTexture::getTextureRef()
{
	return fbo.getTextureReference();
}

void WaveMeshTexture::update()
{
	float deltatime = ofGetElapsedTimef() - lasttime;
	lasttime = ofGetElapsedTimef();


	time[0] += deltatime * speedLeft.get()*0.1;
	time[1] += deltatime * speedFront.get()*0.1;
	time[2] += deltatime * speedZ.get() * 0.01;

	render();
}

void WaveMeshTexture::render()
{
	float cx = getWidth() / 2.0;
	float cy = getHeight() / 2.0;

	fbo.begin();
	ofClear(0, 0, 0, 255);
	shader.begin();
	ofSetColor(255,255,255);
  ofTranslate(cx, cy - 250, -100);
	ofRotateX(60);
	ofRotateZ(rotateZ);
	ofTranslate(0,-cy, -30);


	shader.setUniform3f("offset", time[0], time[1], time[2]);
	shader.setUniform1f("amp", amplitude);
	shader.setUniform1f("fadewidth", 800);

	if(renderMode == RenderMode::RM_WIRE)
		plane.drawWireframe();
	else if (renderMode == RenderMode::RM_POINT)
		plane.drawVertices();
	else {
		plane.draw();
	}
	shader.end();

	fbo.end();
}

void WaveMeshTexture::draw(float x, float y, float w, float h) const
{
	fbo.draw(x, y);
}

void WaveMeshTexture::draw(float x, float y) const
{
	fbo.draw(x, y);
}
void WaveMeshTexture::setRenderMode(RenderMode rm)
{
	renderMode = rm;
}
/*
void WaveMeshTexture::overrideShader(string vertexShader, string fragmentShader)
{
	shader.load(vertexShader, fragmentShader);
}
*/
