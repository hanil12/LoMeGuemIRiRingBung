#pragma once
class Maze;

class MazePlayer
{
public:
	enum Dir
	{
		UP,
		LEFT,
		DOWN,
		RIGHT,

		DIR_COUNT = 4
	};

	struct Vertex
	{
		int y;
		int x;

		int g;
	};

	MazePlayer();
	~MazePlayer();

	void Update();

	void SetMaze(shared_ptr<Maze> maze);
	void Init();

	void FindPath_RightHand();
	void FindPath_DFS();
	void FindPath_BFS();

	bool CanGo(int y, int x);
	void DFS(int y, int x, const Vector& endPos);
	void BFS(int y, int x, const Vector& endPos);

private:
	shared_ptr<Maze> _maze;

	Dir _dir = Dir::UP;
	Vector _pos = {1,1};
	Vector _startPos = {};
	Vector _endPos = {};

	int _pathIndex = 0;
	float _time = 0.0f;

	vector<Vector> _path; // 찾은 길에 대한 정보

	// DFS 정보
	// adjacent 행렬
	// visited ...
	vector<vector<bool>> _visited;
};

