﻿// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <memory>
#include <wrl/client.h>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#include "../DirectXTex/DirectXTex.h"

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"dxguid.lib")

using namespace std;
using namespace DirectX;

// Math
#include "Math/Vector.h"
#include "Math/Transform.h"

// Framework
#include "Core/Device.h"
#include "Core/Render/VertexLayout.h"
#include "Core/Render/VertexBuffer.h"
#include "Core/Render/IndexBuffer.h"
#include "Core/Render/VertexShader.h"
#include "Core/Render/PixelShader.h"
#include "Core/Texture/SamplerState.h"
#include "Core/Texture/BlendState.h"
#include "Core/Texture/StateManager.h"
#include "Core/Texture/SRV.h"
#include "Core/Texture/SRVManager.h"

// Matrix
#include "Core/Render/ConstantBuffer.h"
#include "Core/Render/BufferLayOut.h"

// Utility
#include "Utility/InputManager.h"
#include "Utility/TimeManager.h"

// Collider
#include "Math/Collider/RectCollider.h"
#include "Math/Collider/CircleCollider.h"

// Bagic Obj
#include "Contents/Quad.h"
#include "Contents/Sprite.h"

#include "Contents/Action.h"
#include "Contents/Effect/Effect.h"

// Scene
#include "Scene/Scene.h"

// Program
#include "Program/Program.h"

// Macro
#include "GMacro.h"

extern HWND hWnd;
extern Vector mousePos;