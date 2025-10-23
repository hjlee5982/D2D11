#pragma once

class Texture : public Asset
{
public:
	Texture() : Asset(EAssetType::Texture) {}
public:
	virtual void Load(const wstring& path) override {}
	virtual void Save(const wstring& path) override {}
public:
	void CreateTexture(const wstring& path);
public:
	ComPtr<ID3D11Texture2D>          GetTexture();
	ComPtr<ID3D11ShaderResourceView> GetSRV();
	Vector2                          GetTextureSize();
	ScratchImage&                    GetImage();
public:
	void SetSRV(ComPtr<ID3D11ShaderResourceView> srv);
private:
	ComPtr<ID3D11Texture2D>          _texture;
	ComPtr<ID3D11Texture2D>          _renderTargetTexture;
	ComPtr<ID3D11RenderTargetView>   _renderTargetView;
	ComPtr<ID3D11ShaderResourceView> _shaderResourceView;
private:
	ScratchImage _image;
	Vector2      _imagesize;
};

