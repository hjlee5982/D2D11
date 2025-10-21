#pragma once

class Material : public Asset
{
public:
	Material() : Asset(EAssetType::Material) {}
public:
	virtual void Load(const wstring& path) override {}
	virtual void Save(const wstring& path) override {}
public:
	void PushData();
public:
	sptr<class Shader>& GetShader();
public:
	void SetShader(sptr<class Shader> shader);
	void SetTexture(sptr<class Texture> texture);
private:
	sptr<class Shader>  _shader;
	sptr<class Texture> _texture;
};

