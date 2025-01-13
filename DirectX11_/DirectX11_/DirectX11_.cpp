// DirectX11_.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "DirectX11_.h"

#define MAX_LOADSTRING 100

// Direct X : Direct Access
// => 하드웨어(GPU)에 직접 접근을 도와주는 API를 제공

// CPU vs GPU
// - GPU는 연산장치의 개수가 CPU보다 월등하게 많다.
// - GPU 연산장치는 단순한 계산 처리에 특화되어있다.
// ==> CPU(교수님) vs GPU(초등학생 만명)

// WIN_API => 픽셀찍어서 그리기
// 화면 해상도 : 1920 x 1080개수의 픽셀 계산을 CPU가 하는 것 효율적인가?
// => 초등학생 1만명한테 맡기겠다.

// DX2D => 게임엔진을 만들기.
// 영화 촬영
// 총감독 / 프로그래머
// 영화사 / 게임엔진
// 세트장 / World
// 카메라 / 카메라
// 배우 / Actor
// 조명 / Light

// 렌더링파이프라인(3차원 가상에 있는 점들의 집합(메쉬)을 우리가 모니터(2차원)으로 어떻게 변환되는지에 대한 단계)

// com객체
// - 동적할당을 Create/Release.

// 인력사무소장
// 외주를 맡기고 실질적인 공사 대표 뽑기
// 컴퓨터 하드웨어 기능 점검, 리소스 할당(하드웨어 접근에 필요한 리소스 할당)
Microsoft::WRL::ComPtr<ID3D11Device> device;

// 연출감독
// 세트장을 실질적으로 꾸며주는 연출가
// 렌더링 대상 결정(어따 그릴지, 얼마나 그릴지 결정)
// -> 리소스를 그래픽 파이프라인에 바인딩, GPU가 수행할 명령을 지시
Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;

// DX의 인터페이스로써 1개 이상의 표면을 포함하는 얘
// 각각의 표면(버퍼, 텍스쳐)를 출력하기 전에 데이터를 보관한다.
Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;

// 후면버퍼를 가리키는 포인터
// 후면버퍼(지금 당장 그릴 곳)
Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;

// 렌더링파이프라인 단계
Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer; // 정점을 담아놓는 얘
Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader; // 정점에 대한 계산식을 적어놓고, GPU가 수행할 명령을 적어놓는 얘
Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader; // 각 정점을 이었을 때 나와야하는 픽셀을 계산해주는 얘
Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout; // 보낸 정보들의 설명을 기입

HWND hWnd;

struct Vertex
{
    Vertex() {}
    Vertex(XMFLOAT3 pos) : pos(pos) {}

    XMFLOAT3 pos;
};

void InitDevice();
void Render();

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DIRECTX11, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DIRECTX11));

    InitDevice();

    MSG msg = {};

    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            // 최적화
            // 메인루프
            Render();
        }
    }

    return (int) msg.wParam;
}

//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DIRECTX11));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DIRECTX11);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


void InitDevice()
{
    RECT rc;
    GetClientRect(hWnd, &rc);
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };

    UINT featureSize = ARRAYSIZE(featureLevels);

    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.BufferCount = 1;
    sd.BufferDesc.Width = width;
    sd.BufferDesc.Height = height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    // Numerator / Denominator => 화면 프레임 갱신 속도
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow= hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = true;

    D3D11CreateDeviceAndSwapChain
    (
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        0,
        D3D11_CREATE_DEVICE_DEBUG,
        featureLevels,
        featureSize,
        D3D11_SDK_VERSION,
        &sd,
        swapChain.GetAddressOf(),
        device.GetAddressOf(),
        nullptr,
        deviceContext.GetAddressOf()
    );

    Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;

    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)backBuffer.GetAddressOf());
    device->CreateRenderTargetView(backBuffer.Get(), nullptr, renderTargetView.GetAddressOf());

    deviceContext->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), nullptr);

    D3D11_VIEWPORT vp;
    vp.Width = width;
    vp.Height = height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    deviceContext->RSSetViewports(1, &vp);

    // 렌더링파이프라인

    D3D11_INPUT_ELEMENT_DESC layOut[] = 
    {
        {
            "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,
            D3D11_INPUT_PER_VERTEX_DATA,0
        }
    };

    UINT layoutSize = ARRAYSIZE(layOut);

    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    // VertexShader, InputLayOut
    Microsoft::WRL::ComPtr<ID3DBlob> vertexBlob; // Shader를 읽어주는 얘
    D3DCompileFromFile(L"Shader/TutorialShader.hlsl", nullptr, nullptr,
    "VS", "vs_5_0", flags, 0, vertexBlob.GetAddressOf(),nullptr);

    device->CreateVertexShader(vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(), nullptr, vertexShader.GetAddressOf());
    device->CreateInputLayout(layOut,layoutSize, vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(), inputLayout.GetAddressOf());

    Microsoft::WRL::ComPtr<ID3DBlob> pixelBlob;
    D3DCompileFromFile(L"Shader/TutorialShader.hlsl", nullptr, nullptr,
    "PS", "ps_5_0", flags, 0, pixelBlob.GetAddressOf(), nullptr);

    device->CreatePixelShader(pixelBlob->GetBufferPointer(), pixelBlob->GetBufferSize(), nullptr, pixelShader.GetAddressOf());

    vector<Vertex> verices;
    // 사각형
    // 시계방향으로 정점을 배치해야 볼 수 있는 면이 나온다.
    verices.push_back(XMFLOAT3(0.0f, 0.5f, 0.0f)); // 위
    verices.push_back(XMFLOAT3(0.5f, -0.5f, 0.0f)); // 오른쪽 아래
    verices.push_back(XMFLOAT3(-0.5f, -0.5f, 0.0f)); // 왼쪽 아래

    D3D11_BUFFER_DESC bd = {};
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(Vertex) * verices.size();
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = verices.data();

    device->CreateBuffer(&bd, &initData, vertexBuffer.GetAddressOf());
}

void Render()
{
    // 바탕화면
    FLOAT myColorR = 0.0f;
    FLOAT myColorG = 0.0f;
    FLOAT myColorB = 0.0f;

    FLOAT clearColor[4] = {myColorR, myColorG,myColorB, 1.0f};

    deviceContext->ClearRenderTargetView(renderTargetView.Get(), clearColor);

    // IA : Input Assembler : 입력 병합
    deviceContext->IASetInputLayout(inputLayout.Get());

    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    deviceContext->VSSetShader(vertexShader.Get(), nullptr, 0);
    deviceContext->PSSetShader(pixelShader.Get() ,nullptr, 0);

    // 정점의 개수
    deviceContext->Draw(3,0);

    swapChain->Present(0,0);
}