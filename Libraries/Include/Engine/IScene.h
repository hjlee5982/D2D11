#pragma once

class IScene abstract : public IJson
{
public:
	virtual void InitializeScene() abstract;
};

