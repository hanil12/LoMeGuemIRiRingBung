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
	int g = 0; // ����ġ
};

// ���ͽ�Ʈ�� (������)
// - BFS
// - �켱���� ť ���
vector<bool> discovered;
vector<int> parent;
vector<int> best; // �ش� ����� �ּ� ����ġ�� ����

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

		// ���� �߰��� ���� �� ���� ��ο���.
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
			// here �� there ���� ��
			if(here == there)
				continue;

			// here�� there�� ��������
			if(adjacent[here][there] == -1)
				continue;

			// ���� ���� ��ġ�� best�� + there������ ������ ����
			int nowCost = best[here] + adjacent[here][there];

			// ������ �߰��� ���� best�� �� �۾Ҵ�?
			if(nowCost >= best[there])
				continue;

			Vertex thereV = Vertex(there, nowCost);
			pq.push(thereV);
			best[there] = nowCost;
			parent[there] = here;
		}
	}
}

// �������
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

	// 0���� 6���� �����ϴ� �ּ� ����ġ
	cout << best[6] << endl;

	for (int i = 0; i < adjacent.size(); i++)
	{
		cout << i << "�� �θ� : " << parent[i] << endl;
		cout << "0���� "<<i <<"������ �ּ� ����ġ: " << best[i] << endl;
	}

	return 0;
}