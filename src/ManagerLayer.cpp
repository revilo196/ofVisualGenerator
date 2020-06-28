#include "ManagerLayer.h"

#include "CircleGrow.h"
#include "ParticleGrowTexture.h"
#include "ParticleSystemTexture.h"
#include "StripeSpiral.h"
#include "SphereGrow.h"
#include "StripeCubes.h"
#include "WaveMeshTexture.h"
#include "WaveMeshAdvTex.h"
#include "SpectrumVisu.h"

int ManagerLayer::globalMngLayCont = 0;

void ManagerLayer::setup()
{
	all.setName("LMG" + ofToString(globalMngLayCont));
	fader.setName("fader");
	mng.setup();
	config.setName("config");
	all.add(fader);;
	all.add(config);

	globalMngLayCont++;
}

void ManagerLayer::update()
{
	assert(textures.size() == alphafader.size());
	for (size_t i = 0; i < textures.size(); i++) {
		textures[i]->setAlpha(alphafader[i]);
		textures[i]->setBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
	}

	mng.update();
}

template<typename T>
T * ManagerLayer::createLayer(float defalut_alpha)
{	
	static_assert(std::is_base_of<ofxLayer::Layer, T>::value, "Derived not derived from BaseClass");
	static_assert(std::is_base_of<VjObject, T>::value, "Derived not derived from BaseClass");

	T * lnew = mng.createLayer<T>(defalut_alpha);

	textures.push_back(lnew);
	alphafader.emplace_back(ofToString(counter), defalut_alpha, 0.0, 1.0);
	fader.add(alphafader.back());

	VjObject * cnew = lnew;

	configs.push_back(cnew->getParameterGroup());
	configs.back().setName(ofToString(counter));
	config.add(configs.back());

	counter++;
	return lnew;
}

void ManagerLayer::draw() 
{
	mng.draw();
}



void ManagerLayer::setupLayerByConfig(ofxXmlSettings layersettings)
{
	int num = layersettings.getNumTags("efx");
	const float def_alpha = 0.0;
	for (int i = 0; i < num; i++) {
		string efx_name = layersettings.getValue("efx", "", i);
		if (efx_name == "CircleGrow")                  this->createLayer<CircleGrow>(def_alpha);
		else if (efx_name == "ParticleGrowTexture")    this->createLayer<ParticleGrowTexture>(def_alpha);
		else if (efx_name == "ParticleSystemTexture")  this->createLayer<ParticleSystemTexture>(def_alpha);
		else if (efx_name == "StripeSpiral")           this->createLayer<StripeSpiral>(def_alpha);
		else if (efx_name == "SphereGrow")             this->createLayer<SphereGrow>(def_alpha);
		else if (efx_name == "StripeCubes")            this->createLayer<StripeCubes>(def_alpha);
		else if (efx_name == "WaveMeshTexture")        this->createLayer<WaveMeshTexture>(def_alpha);
		else if (efx_name == "WaveMeshAdvTex")         this->createLayer<WaveMeshAdvTex>(def_alpha);
		else if (efx_name == "SpectrumVisu")         this->createLayer<SpectrumVisu>(def_alpha);

	}
}

void ManagerLayer::setupAllLayers()
{
	const float def_alpha = 0.0;
	this->createLayer<CircleGrow>(def_alpha);
	this->createLayer<ParticleGrowTexture>(def_alpha);
	this->createLayer<ParticleSystemTexture>(def_alpha);
	this->createLayer<StripeSpiral>(def_alpha);
	this->createLayer<SphereGrow>(def_alpha);
	this->createLayer<StripeCubes>(def_alpha);
	this->createLayer<WaveMeshTexture>(def_alpha);
	this->createLayer<WaveMeshAdvTex>(def_alpha);
}

void ManagerLayer::setupParamRouter()
{
	paraRouter.add(routTo.set("to", 0, 0 ,configs.size()-1));


	for (int i = 0; i < 12; i++) {
		ofParameter<float> p0("f" + ofToString(i), 0.0, 0.0, 1.0);
		p0.addListener(this, &ManagerLayer::updateParamRouterf);
		paraRouter.add(p0);
	}

	for (int i = 0; i < 12; i++) {
		ofParameter<bool> p0("b" + ofToString(i), 0.0, 0.0, 1.0);
		p0.addListener(this, &ManagerLayer::updateParamRouterb);
		paraRouter.add(p0);
	}

	for (int i = 0; i < 2; i++) {
		ofParameter<ofFloatColor> p0("c" + ofToString(i), 0.0, 0.0, 1.0);
		p0.addListener(this, &ManagerLayer::updateParamRouterc);
		paraRouter.add(p0);
	}


	routTo.addListener(this, &ManagerLayer::switchRoutionTo);


	
}

void ManagerLayer::switchRoutionTo(int &val)
{

	//copy next LayerConfig in the Switch to avoid overriding
	ofParameterGroup g = configs[val];
	int cntf = 0;
	int cntb = 0;
	int cntc = 0;
	for (int i = 0; i < g.size(); i++) {
		
		string type = g.getType(i);

		if (type == "class ofParameter<float>") {
			paraRouter.getFloat("f" + ofToString(cntf)) = g.getFloat(i);
			cntf++;
		}
		else if (type == "class ofParameter<bool>") {
			paraRouter.getBool("b" + ofToString(cntb)) = g.getBool(i);

			cntb++;
		}
		else if (type == "class ofParameter<class ofColor_<unsigned char> >") {
			ofColor c = g.getColor(i);
			paraRouter.getFloatColor("c" + ofToString(cntc)) = ofFloatColor(c.r / 255.0 , c.g / 255.0 , c.b / 255.0 , c.a / 255.0);

			cntc++;
		}
		else if (type == "class ofParameter<class ofColor_<float> >") {
			paraRouter.getFloatColor("c" + ofToString(cntb)) = g.getFloatColor(i);
			cntc++;
		}


	}

}

void ManagerLayer::updateParamRouter()
{

	// modiyfy current Config;
	ofParameterGroup g = configs[routTo];
	int cntf = 0;
	int cntb = 0;
	int cntc = 0;
	for (int i = 0; i < g.size(); i++) {
		string type = g.getType(i);

		if (type == "class ofParameter<float>") {
			g.getFloat(i) = paraRouter.getFloat("f" + ofToString(cntf));
			cntf++;
		}
		else if (type == "class ofParameter<bool>") {
			g.getBool(i) = paraRouter.getBool("b" + ofToString(cntb));

			cntb++;
		}
		else if (type == "class ofParameter<class ofColor_<unsigned char> >") {
			ofFloatColor c = paraRouter.getFloatColor("c" + ofToString(cntc));
			g.getColor(i) = ofColor(c.r *255, c.g*255, c.b*255, c.a*255);
			cntc++;
		}
		else if (type == "class ofParameter<class ofColor_<float> >") {
			g.getFloatColor(i) = paraRouter.getFloatColor("c" + ofToString(cntb));
			cntc++;
		}
	}

	//cout << "update" << endl;

}

void ManagerLayer::updateParamRouterf(float & f)
{
	updateParamRouter();
}

void ManagerLayer::updateParamRouterb(bool & f)
{
	updateParamRouter();
}

void ManagerLayer::updateParamRouterc(ofFloatColor & f)
{
	updateParamRouter();
}
