#include "framework.h"
#include "MazeScene.h"

#include "Contents/GameObject/Maze/Block.h"
#include "Contents/GameObject/Maze/Maze.h"
#include "Contents/GameObject/Maze/MazePlayer.h"

MazeScene::MazeScene()
{
	_maze = make_shared<Maze>();
	_player = make_shared<MazePlayer>();
}

MazeScene::~MazeScene()
{
}

void MazeScene::PostInitilize()
{
	_player->SetMaze(_maze);
	_player->Init();
	_player->RightHand();
}

void MazeScene::Update()
{
	_maze->Update();
	_player->Update();
}

void MazeScene::Render(HDC hdc)
{
	_maze->Render(hdc);
}
