#pragma once

class Object abstract
{
public:
	virtual ~Object() = default;
public:
	const string& GetName();
protected:
	string _name;
};

