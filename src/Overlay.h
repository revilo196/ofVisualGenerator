#pragma once
#include "TextureGen.h"

class Overlay : public TextureGen
{

public:
	explicit Overlay(string name = "Overlay") : TextureGen(name) {}
	~Overlay() {}
	virtual void setTextureIn(ofTexture& texture) { textureIn = texture; }
	
protected:
	ofTexture textureIn;
private:
	Overlay();

};

