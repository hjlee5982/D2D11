#pragma once

#include "TestGameObject.h"

class TestScene
{
public:
	TestGameObject* CreateObject();
public:
	void Save(const string& path);
	void Load(const string& path);
private:
	List<uptr<TestGameObject>> _objects;
};

