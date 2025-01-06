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

	struct Vertex_Djikstra
	{
		Vertex_Djikstra(int y, int x, int g) : y(y), x(x), g(g) {}

		int y;
		int x;

		int g;

		bool operator<(const Vertex_Djikstra& other) const
		{
			return g < other.g;
		}

		bool operator>(const Vertex_Djikstra& other) const
		{
			return g > other.g;
		}
	};

	struct Vertex
	{
		Vertex(int y, int x) : y(y), x(x) {}

		int y;
		int x;

		float g = 0.0f;
		float h = 0.0f; // 휴리스틱 함수
		float f = 0.0f; // g + h

		bool operator<(const Vertex& other) const
		{
			return f < other.f;
		}
		bool operator>(const Vertex& other) const
		{
			return f > other.f;
		}
	};

	MazePlayer();
	~MazePlayer();

	void Update();

	void SetMaze(shared_ptr<Maze> maze);
	void Init();

	void FindPath_RightHand();
	void FindPath_DFS();
	void FindPath_BFS();
	void FindPath_Djikstra();
	void FindPath_Astar();

	bool CanGo(int y, int x);
	void DFS(int y, int x, const Vector& endPos);
	void BFS(int y, int x, const Vector& endPos);
	void Djikstra(int y, int x, const Vector& endPos);
	void Astar(int y, int x, const Vector& endPos);

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

