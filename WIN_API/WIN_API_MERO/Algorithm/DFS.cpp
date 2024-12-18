#include <queue>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

using namespace std;

// DFS, BFS
// arr[10]
vector<vector<bool>> adjacent;
vector<bool> visited;


// �������
void CreateGraph_Matrix()
{
	adjacent.resize(7, vector<bool>(7, false));
	visited = vector<bool>(7, false);
	// 7 x 7
	//    0   1   2   3   4   5   6
	// 0  T   T   T   F   F   F   F
	// 1  T   T   F   F   T   T   F
	// 2  T   F   T   T   F   F   F
	// 3  F   F   T   T   F   F   F
	// 4  F   T   F   F   T   F   T
	// 5  F   T   F   F   F   T   F
	// 6  F   F   F   F   T   F   T

	adjacent[0][0] = true;
	adjacent[0][1] = true;
	adjacent[0][2] = true;

	adjacent[1][0] = true;
	adjacent[1][1] = true;
	adjacent[1][4] = true;
	adjacent[1][5] = true;

	adjacent[2][0] = true;
	adjacent[2][2] = true;
	adjacent[2][3] = true;

	adjacent[3][2] = true;
	adjacent[3][3] = true;

	adjacent[4][1] = true;
	adjacent[4][4] = true;
	adjacent[4][6] = true;

	adjacent[5][1] = true;
	adjacent[5][5] = true;

	adjacent[6][4] = true;
	adjacent[6][6] = true;
}

// ����Լ�(�Լ��� ������������ �̿��Ͽ�)
void DFS(int here)
{
	visited[here] = true;
	cout << here << "�湮!!" << endl;

	for (int there = 0; there < adjacent.size(); there++)
	{
		// �ڱ��ڽ����� Ȯ��
		if(here == there)
			continue;

		// �������ִ��� Ȯ��
		if(adjacent[here][there] == false)
			continue;

		// �湮�� �Ǿ��־����� Ȯ��
		if(visited[there] == true)
			continue;

		DFS(there);
	}
}

void DFS_ALL()
{
	int count = 0;
	for (int i = 0; i < adjacent.size(); i++)
	{
		if (visited[i] == false)
		{
			count++;
			DFS(i);
		}
	}

	cout << count << endl;
}

int main()
{
	CreateGraph_Matrix();
	DFS_ALL();

	return 0;
}