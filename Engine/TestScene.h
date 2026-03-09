#pragma once

class TestScene
{
public:
	class TestGameObject* CreateObject();
public:
	void Save(const string& path);
	void Load(const string& path);
private:
	List<class TestGameObject*> _objects;
public:
	Dictionary<uint64_t, class TestGameObject*> _objectMap;
public:
	class TestGameObject* FindObject(uint64_t id);
};

