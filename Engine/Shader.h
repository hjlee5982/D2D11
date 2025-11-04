#pragma once

class Shader : public Asset
{
public:
	Shader() : Asset(EAssetType::Shader) {}
public:
	void CreateShader(const wstring& path);
	void Bind();
private:
	ComPtr<ID3D11VertexShader>   _vs;
	ComPtr<ID3D11PixelShader>    _ps;
private:
	ComPtr<ID3D11InputLayout> _inputLayout;
};