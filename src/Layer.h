#pragma once
#include "TextureGen.h"
#include "ofxGui.h"

class Layer :
	public TextureGen
{
public:
	Layer(string name = "layer");
	~Layer();

	virtual void setup(float width, float height) override;
	virtual ofTexture& getTextureRef()	override;
	virtual void update() override;
	virtual void draw(float x, float y, float w, float h) const override;
	virtual void draw(float x, float y) const override;

	void addTextureGen(TextureGen * n_textureGen);
	void setGui(ofxPanel * gui);
	void listenEvent(int &val);
private:
	vector<TextureGen*> textures;
	int lastval = 0;


	ofxPanel * gui = nullptr;
	ofxPanel guiChoose;
	ofxPanel guiLayer;

	bool isSetup = false;
	ofParameter<int> choose;

};

