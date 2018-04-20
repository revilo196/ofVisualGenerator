#include "VjObject.h"


VjObject::VjObject(std::string name)
{
	this->nameParameter = name;
	this->parameters.add(this->nameParameter);
}

VjObject::~VjObject()
{
}

void VjObject::addParameter(ofAbstractParameter & param)
{
	parameters.add(param);
}


ofParameterGroup VjObject::getParameterGroup()
{
	return parameters;
}

void VjObject::clearParameter()
{
	
	for (int i = 0; i < parameters.size(); i++) {
		parameters.remove(i);
	}
	this->parameters = ofParameterGroup();
	this->parameters.add(this->nameParameter);
}

void VjObject::setName(string name)
{
	nameParameter = name;
}

string VjObject::getName()
{
	return nameParameter.get();
}
