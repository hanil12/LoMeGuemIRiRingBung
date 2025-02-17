#include "framework.h"
#include "Program.h"

#include "Scene/TutorialScene.h"
#include "Scene/SolarSystemScene.h"
#include "Scene/BowScene.h"
#include "Scene/CollisionScene.h"

Program::Program()
{
	_scene = make_shared<BowScene>();

    _view = make_shared<MatrixBuffer>();
    _projection = make_shared<MatrixBuffer>();

    XMMATRIX projectionM = XMMatrixOrthographicOffCenterLH(0,WIN_WIDTH,0,WIN_HEIGHT,0.0f,1.0f);
    _projection->SetData(projectionM);
}

Program::~Program()
{
}

void Program::Update()
{
    InputManager::GetInstance()->Update();
    TimeManager::Instance()->Update();

    _view->Update();
    _projection->Update();

    _scene->PreUpdate();
	_scene->Update();
}

void Program::Render()
{
    // ¹ÙÅÁÈ­¸é
    FLOAT myColorR = 0.0f;
    FLOAT myColorG = 0.0f;
    FLOAT myColorB = 0.0f;

    FLOAT clearColor[4] = {myColorR, myColorG,myColorB, 1.0f};

    DC->ClearRenderTargetView(RTV.Get(), clearColor);
    
    _view->SetVSBuffer(1);
    _projection->SetVSBuffer(2);

    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    ALPHA->SetState();
    _scene->Render();

    _scene->PostRender();

    Device::Instance()->GetSwapChain()->Present(0, 0);
}
