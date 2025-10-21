#pragma once

enum class EAssetType : i8
{
	None = -1,
	Mesh,
	Texture,
	Material,
	Shader,

	End
};

enum
{
	Asset_Type_Count = static_cast<i8>(EAssetType::End)
};

class Asset abstract
{
public:
	Asset(EAssetType type) : _assetType(type) {}
public:
	virtual void Load(const wstring& path) = 0;
	virtual void Save(const wstring& path) = 0;
public:
	EAssetType GetAssetType();
protected:
	EAssetType _assetType = EAssetType::None;
protected:
	wstring _name;
	wstring _path;
};

