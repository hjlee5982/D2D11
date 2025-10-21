#pragma once

/* C++ 헤더 */
#include <Windows.h>
#include <assert.h>
#include <optional>
#include <comdef.h>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <set>
#include <typeinfo>
#include <typeindex>
#include <array>


/* DirectX11 헤더 */
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3d11shader.h>
#include <wrl.h>
#include <DirectXMath.h>
#include <DirectXTex/DirectXTex.h>
#include <DirectXTex/DirectXTex.inl>
#include <DirectXColors.h>
using namespace DirectX;
using namespace Microsoft::WRL;


/* DirectX11 라이브러리 */
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#ifdef _DEBUG
#pragma comment(lib, "DirectXTex/DirectXTex_debug.lib")
#pragma comment(lib, "FX11/Effects11d.lib")
#else
#pragma comment(lib, "DirectXTex/DirectXTex.lib")
#pragma comment(lib, "FX11/Effects11.lib")
#endif

/* Define */
#include "Define.h"
#include "Using.h"
#include "Singleton.h"

/* 사용자 */
#include "Client.h"
#include "Device.h"
#include "Exception.h"

#include "Object.h"
#include "GameObject.h"

#include "Component.h"
#include "Transform.h"
#include "SpriteRenderer.h"

#include "VertexData.h"
#include "Asset.h"