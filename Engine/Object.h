#pragma once

#include "IJson.h"

class Object abstract : public IJson
{
public:
	string name   = "none";
	string tag    = "none";
	bool isActive = true;
};