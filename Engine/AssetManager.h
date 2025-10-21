#pragma once

class Texture;

class AssetManager : public Singleton<AssetManager>
{
	friend class Singleton<AssetManager>;
public:
	virtual void Awake() override;
private:
	void CreateDefaultResource();
};

