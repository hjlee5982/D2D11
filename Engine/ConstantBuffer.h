#pragma once

template<typename T>
class ConstantBuffer
{
public:
	ComPtr<ID3D11Buffer> GetConstantBuffer()
	{
		return _constantBuffer;
	}
public:
	void Create()
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		{
			desc.ByteWidth      = sizeof(T);
			desc.BindFlags      = D3D11_BIND_CONSTANT_BUFFER;
			desc.Usage          = D3D11_USAGE_DYNAMIC;
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		}

		CHECK(Device::Instance().GetDevice()->CreateBuffer(&desc, nullptr, _constantBuffer.GetAddressOf()));
	}
private:
	ComPtr<ID3D11Buffer> _constantBuffer;
};

