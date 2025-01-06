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
    if (_pathIndex >= _path.size())
    {
        _maze->CreateMaze();
        Init();
        FindPath_Astar();
        _maze->SetBlockType(_maze->GetEndPos().y, _maze->GetEndPos().x, Block::BlockType::END);

        return;
    }

    _time += 0.2f;
    if (_time > 1.0f)
    {
        _time = 0.0f;
        _maze->SetBlockType(_pos.y, _pos.x, Block::BlockType::FOOT_PRINT);
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

    stack<Vector> s;

    for (int i = 0; i < _path.size() - 1; i++)
    {
        if(s.empty() == false && s.top() == _path[i + 1])
            s.pop();
        else
            s.push(_path[i]);
    }

    s.push(_path.back());
    // s ... ����Ŭ(���ٰ� ���ƿ��� ��)�̿����� Pop

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
    // TODO : ����
    // 1. adjcent...
    Vector frontPos[4] =
    {
        Vector{0, -1}, // UP
        Vector{-1, 0}, // LEFT
        Vector{0,1}, // DOWN
        Vector{1,0} // RIGHT
    };

    Vector start = _maze->GetStartPos();
    Vector end = _maze->GetEndPos(); // DFS�� ������

    // �湮 ó��
    _visited = vector<vector<bool>>(MAX_Y, vector<bool>(MAX_X, false));
    _pos = start;

    // ù ������ ����
    _visited[start.y][start.x] = true;
    _path.push_back(start);
    DFS(_pos.y, _pos.x, end);
}

void MazePlayer::FindPath_BFS()
{
    BFS(1,1, _maze->GetEndPos());
}

void MazePlayer::FindPath_Djikstra()
{
    Djikstra(1,1,_maze->GetEndPos());
}

void MazePlayer::FindPath_Astar()
{
    Astar(1,1,_maze->GetEndPos()); // A*
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
    // ���� ����
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

        // �������ִ���? , Ȥ�� �� �� �ִ� ������
        if (CanGo(there.y, there.x) == false)
            continue;

        // �湮�Ǿ��ִ���?
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
    Vector frontPos[8] =
    {
        Vector{0,1}, // DOWN
        Vector{1,0}, // RIGHT
        Vector{0, -1}, // UP
        Vector{-1, 0}, // LEFT
        Vector{1,1}, // RIGHTDOWN
        Vector{1,-1}, // RIGHT UP
        Vector{-1, -1}, // LEFT UP
        Vector{-1, 1} // LEFT DOWN
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

        _maze->SetBlockType(here.y, here.x, Block::BlockType::FOOT_PRINT);
        if (here == endPos)
        {
            break;
        }

        for (int i = 0; i < 8; i++)
        {
            Vector there = here + frontPos[i];

            // �������ֳ�?
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

void MazePlayer::Djikstra(int y, int x, const Vector& endPos)
{
    Vector frontPos[8] =
    {
        Vector{0,1}, // DOWN
        Vector{1,0}, // RIGHT
        Vector{0, -1}, // UP
        Vector{-1, 0}, // LEFT
        Vector{1,1}, // RIGHTDOWN
        Vector{1,-1}, // RIGHT UP
        Vector{-1, -1}, // LEFT UP
        Vector{-1, 1} // LEFT DOWN
    };

    vector<vector<Vector>> parent = vector<vector<Vector>>(MAX_Y, vector<Vector>(MAX_X, Vector(-1, -1)));
    vector<vector<bool>> discovered = vector<vector<bool>>(MAX_Y, vector<bool>(MAX_X, false));
    vector<vector<int>> best = vector<vector<int>>(MAX_Y, vector<int>(MAX_X, INT_MAX));
    auto temp = [](const Vertex_Djikstra& a, const Vertex_Djikstra& b)-> bool { return false; };
    priority_queue<Vertex_Djikstra, vector<Vertex_Djikstra>, greater<Vertex_Djikstra>> pq;

    // 1,1
    parent[1][1] = Vector(1, 1);
    best[1][1] = 0;
    discovered[1][1] = true;
    Vertex_Djikstra startV(1,1,0);
    pq.push(startV);

    while (true)
    {
        if(pq.empty()) break;

        Vertex_Djikstra hereV = pq.top();
        pq.pop();

        if(hereV.x == endPos.x && hereV.y == endPos.y)
            break;

        _maze->SetBlockType(hereV.y, hereV.x, Block::BlockType::FOOT_PRINT);

        // ������ �߾��� �긦 �ôµ� ���� �߰��� ��ΰ� �� ���� ��ο���.
        if(best[hereV.y][hereV.x] < hereV.g)
            continue;

        for (int i = 0; i < 8; i++)
        {
            Vector there = Vector(hereV.x, hereV.y) + frontPos[i];

            // ����
            if(!CanGo(there.y, there.x)) continue;
            // cost ���ϱ�
            int newCost = 0;
            if(i < 4)
                newCost = best[hereV.y][hereV.x] + 10;
            else
                newCost = best[hereV.y][hereV.x] + 14;
            // ������ü ���
            if(best[there.y][there.x] < newCost)
                continue;

            Vertex_Djikstra thereV(there.y, there.x, newCost);
            pq.push(thereV);
            parent[there.y][there.x] = Vector(hereV.x, hereV.y);
            best[there.y][there.x] = newCost;
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

void MazePlayer::Astar(int y, int x, const Vector& endPos)
{
    Vector frontPos[8] =
    {
        Vector{0,1}, // DOWN
        Vector{1,0}, // RIGHT
        Vector{0, -1}, // UP
        Vector{-1, 0}, // LEFT
        Vector{1,1}, // RIGHTDOWN
        Vector{1,-1}, // RIGHT UP
        Vector{-1, -1}, // LEFT UP
        Vector{-1, 1} // LEFT DOWN
    };

    vector<vector<Vector>> parent = vector<vector<Vector>>(MAX_Y, vector<Vector>(MAX_X, Vector(-1, -1)));
    vector<vector<bool>> discovered = vector<vector<bool>>(MAX_Y, vector<bool>(MAX_X, false));
    vector<vector<float>> best = vector<vector<float>>(MAX_Y, vector<float>(MAX_X, 100000.0f));
    auto temp = [](const Vertex_Djikstra& a, const Vertex_Djikstra& b)-> bool { return false; };
    priority_queue<Vertex, vector<Vertex>, greater<Vertex>> pq;

    // 1,1
    parent[1][1] = Vector(1, 1);
    discovered[1][1] = true;
    Vertex startV(1, 1);
    startV.g = 0.0f;
    startV.h = (endPos - Vector(1,1)).Length();
    startV.f = startV.g + startV.h;

    best[1][1] = startV.f;
    pq.push(startV);

    while (true)
    {
        if(pq.empty()) break;

        Vertex hereV = pq.top();
        pq.pop();

        if(hereV.y == endPos.y && hereV.x == endPos.x)
            break;

        _maze->SetBlockType(hereV.y, hereV.x, Block::BlockType::FOOT_PRINT);

        if(best[hereV.y][hereV.x] < hereV.f)
            continue;

        for (int i = 0; i < 8; i++)
        {
            Vector there = Vector(hereV.x, hereV.y) + frontPos[i];

            if(CanGo(there.y, there.x) == false) continue;

            float newCostG;
            if(i < 4)
                newCostG = hereV.g + 1.0f;
            else 
                newCostG = hereV.g + 1.4f;

            float newCostH = (endPos - there).Length(); // �츮�� �޸���ƽ
            float newCost = newCostG + newCostH;

            if(best[there.y][there.x] < newCost) continue;

            Vertex thereV(there.y, there.x);
            thereV.g = newCostG;
            thereV.h = newCostH;
            thereV.f = newCost;

            pq.push(thereV);
            parent[there.y][there.x] = Vector(hereV.x, hereV.y);
            best[there.y][there.x] = newCost;
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
