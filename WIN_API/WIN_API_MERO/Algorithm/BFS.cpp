#include <queue>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

using namespace std;

vector<vector<bool>> adjacent;

// �������
void CreateGraph_Matrix()
{
	adjacent.resize(7, vector<bool>(7, false));
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

// BFS
// ���� �켱 �켱 Ž��

vector<bool> discovered;
vector<int> parent;

void BFS(int start)
{
	discovered = vector<bool>(adjacent.size());
	parent = vector<int>(adjacent.size(), -1);
	queue<int> q;

	// ������ ����
	q.push(start);
	parent[start] = start;
	discovered[start] = true;

	while (true)
	{
		if(q.empty())
			break;

		int here = q.front();

		q.pop();

		for (int there = 0; there < adjacent.size(); there++)
		{
			// ����?
			if(adjacent[here][there] == false)
				continue;

			// �湮?
			if(discovered[there] == true)
				continue;

			q.push(there);
			parent[there] = here;
			discovered[there] = true;
		}
	}
}

int main()
{
	CreateGraph_Matrix();
	BFS(0);

	// 6�� 0�� ������ �� �Ǿ��ֳ�?, �� �� �Ÿ�(��ŭ ���� Ÿ�� ���ߵǳ�)�� �󸶳� �ǳ�?
	int check = 6;
	int count = 0;

	while (true)
	{
		if (check == -1)
		{
			cout << "0�� 6�� ����Ǿ����� �ʽ��ϴ�." << endl;
			break;
		}

		if (check == 0)
		{
			cout << "0�� 6�� ����Ǿ��ֽ��ϴ�." << endl;
			count++;
			cout << count << endl;
			break;
		}

		cout << check << endl;
		check = parent[check];
		count++;
	}

	return 0;
}