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

    // ���� �÷��̾� ��ġ
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
    // ��������� �� �� �ִ� ���(pos)���� _path���ٰ� ��Ƴ��� ����
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
        // ������ �����ߴ�.
        if (_pos == _endPos)
        {
            _path.push_back(_pos);
            break;
        }

        // �̵�
        //            LEFT(1)         4
        int newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT; // ������ ȸ�� => % ��ȯ ������ �̿��� ����
        Vector oldDirVector = frontPos[_dir]; // ���� �� �չ���
        Vector newDirVector = frontPos[newDir]; // ���� �� ������

        Vector rightPos = _pos + newDirVector;
        Vector forwardPos = _pos + oldDirVector;
        if (CanGo(rightPos.y, rightPos.x)) // �� �������� �շ��ֳ�
        {
            // ���������� ȸ���ϰ� 1ĭ ������
            _dir = static_cast<Dir>(newDir);
            _pos = rightPos;
            _path.push_back(_pos);
        }
        else if (CanGo(forwardPos.y, forwardPos.x)) // �������� ���������� ���� ���� �״�� ����.
        {
            // ���� �������� 1ĭ ������
            _pos = forwardPos;
            _path.push_back(_pos);
        }
        else // �����ʵ� �����ְ�, �յ� �����ִ�.
        {
            // �������� ȸ��
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
