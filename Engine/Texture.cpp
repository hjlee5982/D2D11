#include "pch.h"
#include "Texture.h"

void Texture::Load(const wstring& path)
{
    HRESULT hr;

    TexMetadata md;

    wchar_t szExt[20] = {};

    _wsplitpath_s(path.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExt, 20);

    if (!wcscmp(szExt, L".dds") || !wcscmp(szExt, L".DDS"))
    {
        CHECK(hr = ::LoadFromDDSFile(path.c_str(), DDS_FLAGS_NONE, &md, _image));
    }
    else
    {
        CHECK(hr = ::CreateShaderResourceView(Device::Instance().GetDevice().Get(), _image.GetImages(), _image.GetImageCount(), md, _shaderResourceView.GetAddressOf()));
    }

	_imagesize.x = md.width;
	_imagesize.y = md.height;
}

void Texture::Save(const wstring& path)
{
}

void Texture::CreateTexture(i32 width, i32 height)
{
	D3D11_TEXTURE2D_DESC textureDesc;
	ZeroMemory(&textureDesc, sizeof(textureDesc));
	{
		textureDesc.Width            = width;
		textureDesc.Height           = height;
		textureDesc.MipLevels        = 1;
		textureDesc.ArraySize        = 1;
		textureDesc.Format           = DXGI_FORMAT_R32G32B32A32_FLOAT;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.Usage            = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags        = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags   = 0;
		textureDesc.MiscFlags		 = 0;
	}
	CHECK(Device::Instance().GetDevice()->CreateTexture2D(&textureDesc, nullptr, _renderTargetTexture.GetAddressOf()));

	CD3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
	ZeroMemory(&renderTargetViewDesc, sizeof(renderTargetViewDesc));
	{
		renderTargetViewDesc.Format             = textureDesc.Format;
		renderTargetViewDesc.ViewDimension      = D3D11_RTV_DIMENSION_TEXTURE2D;
		renderTargetViewDesc.Texture2D.MipSlice = 0;
	}
	CHECK(Device::Instance().GetDevice()->CreateRenderTargetView(_renderTargetTexture.Get(), &renderTargetViewDesc, _renderTargetView.GetAddressOf()));

	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
	ZeroMemory(&shaderResourceViewDesc, sizeof(shaderResourceViewDesc));
	{
		shaderResourceViewDesc.Format                    = textureDesc.Format;
		shaderResourceViewDesc.ViewDimension             = D3D11_SRV_DIMENSION_TEXTURE2D;
		shaderResourceViewDesc.Texture1D.MostDetailedMip = 0;
		shaderResourceViewDesc.Texture2D.MipLevels       = 1;
	}
	CHECK(Device::Instance().GetDevice()->CreateShaderResourceView(_renderTargetTexture.Get(), &shaderResourceViewDesc, _shaderResourceView.GetAddressOf()));
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
