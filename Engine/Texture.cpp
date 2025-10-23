#include "pch.h"
#include "Texture.h"

void Texture::CreateTexture(const wstring& path)
{
    TexMetadata md;

    wchar_t szExt[20] = {};

    _wsplitpath_s(path.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExt, 20);

    if (!wcscmp(szExt, L".dds") || !wcscmp(szExt, L".DDS"))
    {
        CHECK(::LoadFromDDSFile(path.c_str(), DDS_FLAGS_NONE, &md, _image));
    }
    else
    {
        CHECK(::LoadFromWICFile(path.c_str(), WIC_FLAGS_NONE, &md, _image));
    }

	CHECK(::CreateShaderResourceView(Device::Instance().GetDevice().Get(), _image.GetImages(), _image.GetImageCount(), md, _shaderResourceView.GetAddressOf()));

    _imagesize.x = md.width;
    _imagesize.y = md.height;
}

ComPtr<ID3D11Texture2D> Texture::GetTexture()
{
	ComPtr<ID3D11Texture2D> texture;

	_shaderResourceView->GetResource((ID3D11Resource**)texture.GetAddressOf());

	return texture;
}

ComPtr<ID3D11ShaderResourceView> Texture::GetSRV()
{
	return _shaderResourceView;
}

Vector2 Texture::GetTextureSize()
{
	return _imagesize;
}

ScratchImage& Texture::GetImage()
{
	return _image;
}

void Texture::SetSRV(ComPtr<ID3D11ShaderResourceView> srv)
{
	_shaderResourceView = srv;
}
