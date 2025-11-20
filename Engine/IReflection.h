#pragma once

class IReflection : public IJson
{
public:
	virtual const uint64_t  GetType() const { return 0; };
	virtual const char* GetTypeName() const { return nullptr; };
};

