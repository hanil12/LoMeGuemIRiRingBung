#include "framework.h"
#include "MazePlayer.h"
#include "Contents/GameObject/Maze/Maze.h"
#include "Contents/GameObject/Maze/Block.h"

MazePlayer::MazePlayer()
{
}

MazePlayer::~MazePlayer()
{
}

void MazePlayer::Update()
{
    if(_pathIndex >= _path.size())
        return;

    _time += 0.1f;
    if (_time > 1.0f)
    {
        _time = 0.0f;
        _pos = _path[_pathIndex];

        _pathIndex++;
    }

    // 현재 플레이어 위치
    _maze->SetBlockType(_pos.y, _pos.x, Block::Block::PLAYER);
}

void MazePlayer::SetMaze(shared_ptr<Maze> maze)
{
    _maze = maze;
}

void MazePlayer::Init()
{
    _pos = {0,0};
    _pathIndex = 0;
    _time = 0.0f;
    _dir = Dir::UP;
    _path.clear();

    if (_maze != nullptr)
    {
        _startPos = _maze->GetStartPos();
        _endPos = _maze->GetEndPos();
    }
}

void MazePlayer::RightHand()
{
    // 우수법으로 갈 수 있는 경로(pos)들을 _path에다가 담아놓을 예정
    _pos = _startPos;
    _path.push_back(_pos);

    Vector frontPos[4] = 
    {
        Vector{0, -1}, // UP
        Vector{-1, 0}, // LEFT
        Vector{0,1}, // DOWN
        Vector{1,0} // RIGHT
    };

    while (true)
    {
        // 끝점에 도달했다.
        if (_pos == _endPos)
        {
            _path.push_back(_pos);
            break;
        }

        // 이동
        //            LEFT(1)         4
        int newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT; // 오른쪽 회전 => % 순환 구조를 이용한 설계
        Vector oldDirVector = frontPos[_dir]; // 지금 내 앞방향
        Vector newDirVector = frontPos[newDir]; // 지금 내 오른쪽

        Vector rightPos = _pos + newDirVector;
        Vector forwardPos = _pos + oldDirVector;
        if (CanGo(rightPos.y, rightPos.x)) // 내 오른쪽이 뚫려있냐
        {
            // 오른쪽으로 회전하고 1칸 움직임
            _dir = static_cast<Dir>(newDir);
            _pos = rightPos;
            _path.push_back(_pos);
        }
        else if (CanGo(forwardPos.y, forwardPos.x)) // 오른쪽이 막혀있으면 가던 방향 그대로 간다.
        {
            // 가던 방향으로 1칸 움직임
            _pos = forwardPos;
            _path.push_back(_pos);
        }
        else // 오른쪽도 막혀있고, 앞도 막혀있다.
        {
            // 왼쪽으로 회전
            int leftDir = (_dir + 1) % DIR_COUNT;
            _dir = static_cast<Dir>(leftDir);
        }
    }

    _pos = _startPos;
}

bool MazePlayer::CanGo(int y, int x)
{

    if(y >= MAX_Y || x >= MAX_X) return false;
    if(y < 0 || x < 0) return false;

    Block::BlockType type = _maze->GetBlockType(y,x);

    switch (type)
    {
    case Block::NONE:
        return false;
    case Block::ABLE:
        return true;
    case Block::DISABLE:
        return false;
    default:
        break;
    }

    return false;
}
