#include "framework.h"
#include "Program.h"

#include "Scenes/PaintScene.h"
#include "Scenes/CollisionScene.h"
#include "Scenes/CannonScene.h"
#include "Scenes/LineScene.h"
#include "Scenes/FortressScene.h"
#include "Scenes/MazeScene.h"

HDC Program::backBuffer = nullptr;

Program::Program()
{
    HDC hdc = GetDC(hWnd);

    backBuffer = CreateCompatibleDC(hdc);
    _hBitMap = CreateCompatibleBitmap(hdc, WIN_WIDTH, WIN_HEIGHT); // ��ȭ��
    SelectObject(backBuffer, _hBitMap);

    _sceneTable["PaintScene"] = make_shared<PaintScene>();
    _sceneTable["CollisionScene"] = make_shared<CollisionScene>();
    _sceneTable["CannonScene"] = make_shared<CannonScene>();
    _sceneTable["LineScene"] = make_shared<LineScene>();
    _sceneTable["FortressScene"] = make_shared<FortressScene>();
    _sceneTable["MazeScene"] = make_shared<MazeScene>();

    _curScene = "MazeScene";

    _sceneTable[_curScene]->PostInitilize();
}

Program::~Program()
{
    DeleteObject(backBuffer);
    DeleteObject(_hBitMap);
}

void Program::Update()
{
    _sceneTable[_curScene]->Update();
}

void Program::Render(HDC hdc)
{
    PatBlt(backBuffer, 0, 0, WIN_WIDTH, WIN_HEIGHT, BLACKNESS);

    // �׸��� �׸�
    _sceneTable[_curScene]->Render(backBuffer);

    // ����
    BitBlt
    (
        hdc,
        0,0,
        WIN_WIDTH, WIN_HEIGHT,
        backBuffer,
        0,0,
        SRCCOPY
    );
}
