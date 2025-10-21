#pragma once

enum class EShaderType
{
	VS,
	PS,
	HS,
	DS,
	GS,

	End
};

class Shader : public Asset
{
public:
	Shader() : Asset(EAssetType::Shader) {}
public:
	virtual void Load(const wstring& path) override {}
	virtual void Save(const wstring& path) override {}
public:
	void CreateShader(const wstring& path);
	void BindShader();
public:
	template<typename T>
	void PushData(const T& data);
private:
	ComPtr<ID3D11VertexShader>   _vs;
	ComPtr<ID3D11PixelShader>    _ps;
private:
	ComPtr<ID3D11InputLayout> _inputLayout;
	D3D11_PRIMITIVE_TOPOLOGY  _topology;
};

