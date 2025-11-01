#pragma once

class IJson abstract
{
public:
	virtual void MakeJson() {};
	virtual void LoadJson() {};
public:
	nlohmann::json _json;
};

