#include <queue>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

using namespace std;

vector<vector<int>> adjacent;

// Vertex
struct Vertex
{
	Vertex() {}
	Vertex(int num, int g) : vertexNum(num), g(g) {}

	bool operator<(const Vertex& other) const
	{
		return g < other.g;
	}

	bool operator>(const Vertex& other) const
	{
		return g > other.g;
	}

	int vertexNum = 0;
	int g = 0; // 가중치
};

// 다익스트라 (시작점)
// - BFS
// - 우선순위 큐 사용
vector<bool> discovered;
vector<int> parent;
vector<int> best; // 해당 노드의 최소 가중치를 기입

void Djikstra(int start)
{
	parent = vector<int>(adjacent.size(), -1);
	best.resize(adjacent.size(), INT_MAX);
	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> pq;

	Vertex startV = Vertex(start, 0);
	best[start] = 0;
	pq.push(startV);
	parent[startV.vertexNum] = startV.vertexNum;

	while (true)
	{
		if(pq.empty() == true) 
		{
			break;
		}

		Vertex hereV = pq.top();
		pq.pop();

		// 전에 발견한 곳이 더 좋은 경로였다.
		if (best[hereV.vertexNum] < hereV.g)
		{
			cout << hereV.vertexNum << endl;
			cout << hereV.g << endl;
			cout << best[hereV.vertexNum] << endl;
			continue;
		}

		for (int there = 0; there < adjacent.size(); there++)
		{
			int here = hereV.vertexNum;
			// here 와 there 같은 곳
			if(here == there)
				continue;

			// here와 there가 인접한지
			if(adjacent[here][there] == -1)
				continue;

			// 지금 나의 위치의 best값 + there까지의 간선의 길이
			int nowCost = best[here] + adjacent[here][there];

			// 이전에 발견한 곳의 best가 더 작았다?
			if(nowCost >= best[there])
				continue;

			Vertex thereV = Vertex(there, nowCost);
			pq.push(thereV);
			best[there] = nowCost;
			parent[there] = here;
		}
	}
}

// 인접행렬
void CreateGraph_Matrix()
{
	adjacent.resize(7, vector<int>(7, -1));

	adjacent[0][0] = 0;
	adjacent[0][1] = 10;
	adjacent[0][2] = 3;

	adjacent[1][0] = 10;
	adjacent[1][1] = 0;
	adjacent[1][4] = 1;
	adjacent[1][5] = 4;

	adjacent[2][0] = 3;
	adjacent[2][2] = 0;
	adjacent[2][3] = 2;

	adjacent[3][2] = 2;
	adjacent[3][3] = 0;
	adjacent[3][4] = 2;

	adjacent[4][1] = 1;
	adjacent[4][3] = 2;
	adjacent[4][4] = 0;
	adjacent[4][6] = 7;

	adjacent[5][1] = 4;
	adjacent[5][5] = 0;

	adjacent[6][4] = 7;
	adjacent[6][6] = 0;
}


int main()
{
	CreateGraph_Matrix();
	Djikstra(0);

	// 0에서 6까지 도달하는 최소 가중치
	cout << best[6] << endl;

	for (int i = 0; i < adjacent.size(); i++)
	{
		cout << i << "의 부모 : " << parent[i] << endl;
		cout << "0부터 "<<i <<"까지의 최소 가중치: " << best[i] << endl;
	}

	return 0;
}