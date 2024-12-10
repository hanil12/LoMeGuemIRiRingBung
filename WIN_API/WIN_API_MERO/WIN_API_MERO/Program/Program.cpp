#include "framework.h"
#include "Program.h"

#include "Scenes/PaintScene.h"
#include "Scenes/CollisionScene.h"
#include "Scenes/CannonScene.h"
#include "Scenes/LineScene.h"
#include "Scenes/FortressScene.h"
#include "Scenes/MazeScene.h"

Program::Program()
{
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
}

void Program::Update()
{
    _sceneTable[_curScene]->Update();
}

void Program::Render(HDC hdc)
{
    _sceneTable[_curScene]->Render(hdc);
}
