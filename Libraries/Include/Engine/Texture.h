#pragma once

#include "Asset.h"

class Texture : public Asset
{
public:
	Texture() : Asset(EAssetType::Texture) {}
public:
	void CreateTexture(const wstring& path);
public:
	ComPtr<ID3D11ShaderResourceView> GetSRV();
private:
	ComPtr<ID3D11ShaderResourceView> _srv;
private:
	Vector2 _textureSize;
};

