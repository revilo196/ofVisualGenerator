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

void VjObject::setName(string name)
{
	nameParameter = name;
}

string VjObject::getName()
{
	return nameParameter.get();
}
