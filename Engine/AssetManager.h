#pragma once

#include "Asset.h"

class Mesh;
class Shader;
class Texture;
class Material;

class AssetManager : public Singleton<AssetManager>
{
public:
	virtual void Awake() override;
private:
	void CreateDefaultResource();
public:
	template<typename T>
	bool Add(const wstring& key, sptr<T> object);

	template<typename T>
	sptr<T> Load(const wstring& key, const wstring& path);

	template<typename T>
	sptr<T> Get(const wstring& key, bool clone = false);

	template<typename T>
	EAssetType GetAssetType();
private:
	// 엔진에서 사용될 기본 에셋들을 생성
	void CreateMesh();
	void CreateShader();
	void CreateTexture();
	void CreateMaterial();
private:
	using KeyAssetPair = Dictionary<wstring, sptr<Asset>>;
	std::array<KeyAssetPair, Asset_Type_Count> _resources;
};

template<typename T>
inline bool AssetManager::Add(const wstring& key, sptr<T> object)
{
	EAssetType assetType = GetAssetType<T>();
	KeyAssetPair& kap = _resources[static_cast<int>(assetType)];

	auto it = kap.find(key);

	if (it != kap.end())
	{
		return false;
	}

	kap[key] = object;

	return true;
}

template<typename T>
inline sptr<T> AssetManager::Load(const wstring& key, const wstring& path)
{
	EAssetType assetType = GetAssetType<T>();
	KeyAssetPair& kap = _resources[static_cast<int>(assetType)];

	auto it = kap.find(key);

	if (it != kap.end())
	{
		return std::static_pointer_cast<T>(it->second);
	}

	sptr<T> obj = makeSptr<T>();
	obj->Load(path);
	kap[key] = obj;

	return obj;
}

template<typename T>
inline sptr<T> AssetManager::Get(const wstring& key, bool clone)
{
	EAssetType assetType = GetAssetType<T>();
	KeyAssetPair& kap = _resources[static_cast<int>(assetType)];

	auto it = kap.find(key);

	if (it != kap.end())
	{
		if (clone == true)
		{
			auto cmp = (it->second)->Clone();

			return std::static_pointer_cast<T>(cmp);
		}
		else
		{
			return std::static_pointer_cast<T>(it->second);
		}
	}

	return nullptr;
}

template<typename T>
inline EAssetType AssetManager::GetAssetType()
{
	if (std::is_same_v<T, Texture>)
	{
		return EAssetType::Texture;
	}
	if (std::is_same_v<T, Mesh>)
	{
		return EAssetType::Mesh;
	}
	if (std::is_same_v<T, Material>)
	{
		return EAssetType::Material;
	}
	if (std::is_same_v<T, Shader>)
	{
		return EAssetType::Shader;
	}

	return EAssetType::None;
}
