#include "pch.h"
#include "Material.h"
#include "Texture.h"

void Material::PushData()
{
	if (_texture != nullptr)
	{
		Device::Instance().GetContext()->PSSetShaderResources(0, 1, _texture->GetSRV().GetAddressOf());
	}
}

sptr<class Shader>& Material::GetShader()
{
	return _shader;
}

void Material::SetShader(sptr<class Shader> shader)
{
	_shader = shader;
}

void Material::SetTexture(sptr<class Texture> texture)
{
	_texture = texture;
}
