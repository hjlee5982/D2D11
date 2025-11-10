#pragma once

class IReflection abstract
{
public:
	virtual const uint64_t  GetType() const = 0;
	virtual const char* GetTypeName() const = 0;
};

