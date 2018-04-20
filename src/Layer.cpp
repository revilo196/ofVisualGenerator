#include "Layer.h"



Layer::Layer(string name) : TextureGen(name) , textures()
{
	choose.set("choose", 0, 0, 0);
	this->addParameter(choose);
}


Layer::~Layer()
{
}

void Layer::setup(float width, float height)
{
	TextureGen::setup(width, height);
	choose.addListener(this, &Layer::listenEvent, 20);

	for (int i = 0; i < (textures.size()); i++) {
		textures[i]->setup(width, height);
	}

	if (textures.size() > 0) {
		choose.set("choose", choose, 0, textures.size()-1 );
		this->addParameter(textures[0]->getParameterGroup());
	}

	this->isSetup = true;
}

ofTexture & Layer::getTextureRef()
{
	if (textures.size() > 0) {
		return textures[choose]->getTextureRef();
	}
}

void Layer::update()
{
	if (textures.size() > 0) {
		textures[choose]->update();
	}
}

void Layer::draw(float x, float y, float w, float h) const
{
	if (textures.size() > 0) {
		textures[choose]->draw(x,y,w,h);
	}
}

void Layer::draw(float x, float y) const
{
	if (textures.size() > 0) {
		textures[choose]->draw(x,y);
	}
}

void Layer::addTextureGen(TextureGen * n_textureGen)
{
	textures.push_back(n_textureGen);

	//if the texture is added during runntime setup it
	if (isSetup) {
		n_textureGen->setup(getWidth(), getHeight());
	}

	choose.set("choose", choose, 0, textures.size()-1);
}

void Layer::setGui(ofxPanel * gui)
{
	this->gui = gui;
	gui->clear();
	guiChoose.setup("Chooser");
	guiChoose.add(choose);
	guiLayer.setup("Layer");
	guiLayer.add(textures[choose]->getParameterGroup());
	gui->add(&guiChoose);
	gui->add(&guiLayer);
}



void Layer::listenEvent(int &val)
{
	if (lastval != val && val >= 0 && val < textures.size()) {
		lastval = val;
		this->clearParameter();
		this->addParameter(choose);
		this->addParameter(textures[choose]->getParameterGroup());

		if (gui != nullptr) {

			guiLayer.clear();
			guiLayer.add(textures[choose]->getParameterGroup());
		}
	}
}
