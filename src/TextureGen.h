#pragma once
#include "ofBaseTypes.h"
#include "VjObject.h"

class TextureGen : public ofBaseDraws, public ofBaseUpdates, public VjObject
{
public:
	TextureGen(string name = "TextureGen") : VjObject(name)
	{

	}
	~TextureGen() {}

	virtual void setup(float width, float height)
	{
		this->height = height;
		this->width = width;
	}

	virtual float getHeight() const override { return height; }
	virtual float getWidth() const override { return width; }
	virtual ofTexture& getTextureRef() = 0;

protected:
	virtual void translateMid() const {
		float cy = getHeight() / 2;
		float cx = getWidth() / 2;

		ofTranslate(cx, cy);
	}



private:
	TextureGen();
	float width;
	float height;

};

