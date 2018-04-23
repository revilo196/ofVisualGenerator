#include "VjObject.h"

const float * VjObject::rms = nullptr;

VjObject::VjObject(std::string name)
{
	this->nameParameter = name;
	this->parameters.add(this->nameParameter);
}

VjObject::~VjObject()
{
}

void VjObject::addParameter(ofAbstractParameter & param, bool rms)
{
	parameters.add(param);
	
	if (param.type() == "class ofParameter<float>" && rms) {
		ofParameter<float> p = param.cast<float>();
		mod.emplace_back(p.getName(), p.get(), p.getMin(), p.getMax());
		act.emplace_back("rms-" + p.getName(), false);
		modg1.add(mod.back());
		modg1.add(act.back());
	}
	else {
		modg1.add(param);
	}

	
}


ofParameterGroup VjObject::getParameterGroup()
{
	return modg1;
}


void VjObject::setName(string name)
{
	nameParameter = name;
}

string VjObject::getName()
{
	return nameParameter.get();
}


void VjObject::updateParms()
{

	for (int i = 0; i < parameters.size(); i++) {
		
		if (parameters.getType(i) == "class ofParameter<float>") {

			ofParameter<float> p = parameters.getFloat(i);

			if (modg1.contains(p.getName()) &&  modg1.getBool("rms-" + p.getName())   && rms != nullptr)
			{
				p = modg1.getFloat(p.getName()) + ((p.getMax() - p.getMin())/ 4) * (*rms) ;
			}
			else {
				p = modg1.getFloat(p.getName());
			}


		}
	}

}
