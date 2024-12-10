#include "framework.h"
#include "MazeScene.h"

#include "Contents/GameObject/Maze/Block.h"
#include "Contents/GameObject/Maze/Maze.h"

MazeScene::MazeScene()
{
	_maze = make_shared<Maze>();
}

MazeScene::~MazeScene()
{
}

void MazeScene::PostInitilize()
{
}

void MazeScene::Update()
{
	_maze->Update();
}

void MazeScene::Render(HDC hdc)
{
	_maze->Render(hdc);
}
