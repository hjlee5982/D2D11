#include "pch.h"
#include "Shader.h"

void Shader::CreateShader(const wstring& path)
{
	_path = L"../Shader/" + path;
	
	ComPtr<ID3DBlob> shaderBlob;
	ComPtr<ID3DBlob> errorBlob;
	UINT compileFlags;

#if defined(DEBUG) || defined(_DEBUG)
	compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	string entry = "main";

	// VS 持失
	CHECK(D3DCompileFromFile(_path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entry.c_str(), "vs_5_0", compileFlags, 0, shaderBlob.GetAddressOf(), errorBlob.GetAddressOf()));
	CHECK(Device::Instance().GetDevice()->CreateVertexShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), nullptr, _vs.GetAddressOf()));
	
	// InputLayout 持失
	D3D11_INPUT_ELEMENT_DESC inputLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TANGENT",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	CHECK(Device::Instance().GetDevice()->CreateInputLayout(inputLayout, 4, shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), _inputLayout.GetAddressOf()));

	Device::Instance().GetContext()->IASetInputLayout(_inputLayout.Get());
	Device::Instance().GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	// PS 持失
	CHECK(D3DCompileFromFile(_path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entry.c_str(), "ps_5_0", compileFlags, 0, shaderBlob.GetAddressOf(), errorBlob.GetAddressOf()));
	CHECK(Device::Instance().GetDevice()->CreatePixelShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), nullptr, _ps.GetAddressOf()));
}

void Shader::BindShader()
{
	Device::Instance().GetContext()->VSSetShader(_vs.Get(), nullptr, 0);
	Device::Instance().GetContext()->PSSetShader(_ps.Get(), nullptr, 0);
}