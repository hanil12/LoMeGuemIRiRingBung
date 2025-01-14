// header.h: 표준 시스템 포함 파일
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
#include <wrl/client.h>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#include "../DirectXTex/DirectXTex.h"

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")

using namespace std;
using namespace DirectX;

// 프로젝트 참조


// 정적라이브러리
// A에서 B에 있는 함수들을 쓰고 싶다.
// => B를 정적라이브러리로 만든다.
// ==> B를 실행시켜서 빌드 파일을 만들고
// => A에게 전달해준다.
// .lib

// 동적라이브러리
// A에 B에 있는 함수들을 쓰고 싶다.
// => B를 동적라이브러리
// ==> B는 A가 실행할 때 같이 실행
// .dll