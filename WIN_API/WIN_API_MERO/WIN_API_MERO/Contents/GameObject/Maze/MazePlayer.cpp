#include "framework.h"
#include "MazePlayer.h"
#include "Contents/GameObject/Maze/Maze.h"
#include "Contents/GameObject/Maze/Block.h"
#include <stack>

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
        _maze->SetBlockType(_pos.y, _pos.x, Block::BlockType::FOOT_PRINT);
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
    _pos = {1,1};
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

void MazePlayer::FindPath_RightHand()
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

    stack<Vector> s;

    for (int i = 0; i < _path.size() - 1; i++)
    {
        if(s.empty() == false && s.top() == _path[i + 1])
            s.pop();
        else
            s.push(_path[i]);
    }

    s.push(_path.back());
    // s ... 사이클(갔다가 돌아오는 길)이였으면 Pop

    _path.clear();
    while (true)
    {
        _path.push_back(s.top());
        s.pop();

        if(s.empty())
            break;
    }
    std::reverse(_path.begin(), _path.end());

    _pos = _startPos;
}

void MazePlayer::FindPath_DFS()
{
    // TODO : 과제
    // 1. adjcent...
    Vector frontPos[4] =
    {
        Vector{0, -1}, // UP
        Vector{-1, 0}, // LEFT
        Vector{0,1}, // DOWN
        Vector{1,0} // RIGHT
    };

    Vector start = _maze->GetStartPos();
    Vector end = _maze->GetEndPos(); // DFS용 부적합

    // 방문 처리
    _visited = vector<vector<bool>>(MAX_Y, vector<bool>(MAX_X, false));
    _pos = start;

    // 첫 시작점 세팅
    _visited[start.y][start.x] = true;
    _path.push_back(start);
    DFS(_pos.y, _pos.x, end);
}

void MazePlayer::FindPath_BFS()
{
    BFS(1,1, _maze->GetEndPos());
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

void MazePlayer::DFS(int y, int x, const Vector& endPos)
{
    // 기저 사항
    Vector here = Vector(x, y);
    if(here == _endPos)
        return;

    Vector frontPos[4] =
    {
        Vector{0,1}, // DOWN
        Vector{1,0}, // RIGHT
        Vector{0, -1}, // UP
        Vector{-1, 0} // LEFT
    };


    _visited[y][x] = true;

    // DFS
    for (int i = 0; i < 4; i++)
    {
        Vector there = here + frontPos[i];

        // 인접해있는지? , 혹은 갈 수 있는 길인지
        if (CanGo(there.y, there.x) == false)
            continue;

        // 방문되어있는지?
        if (_visited[there.y][there.x] == true)
            continue;

        if(there == endPos)
            return;

        _path.push_back(there);
        DFS(there.y, there.x, endPos);
    }
}

void MazePlayer::BFS(int y, int x, const Vector& endPos)
{
    Vector frontPos[4] =
    {
        Vector{0,1}, // DOWN
        Vector{1,0}, // RIGHT
        Vector{0, -1}, // UP
        Vector{-1, 0} // LEFT
    };

    vector<vector<Vector>> parent = vector<vector<Vector>>(MAX_Y, vector<Vector>(MAX_X, Vector(-1,-1)));
    vector<vector<bool>> discovered = vector<vector<bool>>(MAX_Y, vector<bool>(MAX_X, false));
    queue<Vector> q;

    // 1,1
    parent[1][1] = Vector(1,1);
    discovered[1][1] = true;
    q.push(Vector(1,1));

    while (true)
    {
        if(q.empty())
            break;

        Vector here = q.front();
        q.pop();

        if (here == endPos)
        {
            break;
        }

        for (int i = 0; i < 4; i++)
        {
            Vector there = here + frontPos[i];

            // 인접해있냐?
            if(CanGo(there.y, there.x) == false)
                continue;
            if(discovered[there.y][there.x])
                continue;

            discovered[there.y][there.x] = true;
            parent[there.y][there.x] = here;
            q.push(there);
        }
    }

    Vector check = endPos;
    while (true)
    {
        _path.push_back(check);
        if (parent[check.y][check.x] == check)
        {
            break;
        }

        check = parent[check.y][check.x];
    }

    std::reverse(_path.begin(), _path.end());
}
