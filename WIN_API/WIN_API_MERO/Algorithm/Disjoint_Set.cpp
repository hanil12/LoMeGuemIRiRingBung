#include <queue>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

using namespace std;

// ���μ� ����

// Ž���
// : ���� ��Ȳ���� �ּ��� ����� ����� ��� ���󰡴� ��

struct User
{
	int guildId;
};

void GuildSystem()
{
	vector<User> users;

	for (int i = 0; i < 1000; i++)
	{
		User user;
		user.guildId = i;

		users.push_back(user);
	}

	// user 5�� 1�� ��忡 �ҼӵǾ���.
	users[5].guildId = 1;

	// 2 ��忡 ���ִ� ��� �ο����� ���1�� ����
	for (auto& user : users)
	{
		if(user.guildId == 2)
			user.guildId = 1;
	}
}

// 0  2 3 4 5 6 7
// 1
// 2
class Naive_DisJointSet
{
public:
	Naive_DisJointSet(int n)
	{
		_parent = vector<int>(n, 0);

		for (int i = 0; i < n; i++)
		{
			_parent[i] = i;
		}
	}

	//     3   7
	//    4 0 7 
	//    5	1
	// ...6 2
	// FindLeader(2) ... 0
	int FindLeader(int u)
	{
		if(u == _parent[u])
			return u;

		int parent = _parent[u];
		return FindLeader(parent);
	}

	void Merge(int u, int v)
	{
		int uLeader = FindLeader(u);
		int vLeader = FindLeader(v);

		if(uLeader == vLeader)
			return;

		_parent[vLeader] = uLeader;
	}

private:
	vector<int> _parent;
};

class DisJointSet
{
public:
	DisJointSet(int n)
	{
		_parent = vector<int>(n,0);
		_rank = vector<int>(n,1);

		for (int i = 0; i < n; i++)
		{
			_parent[i] = i;
		}
	}

	int FindLeader(int u)
	{
		if (u == _parent[u])
			return u;

		int parent = _parent[u];
		return FindLeader(parent);
	}
	 
	// u         v
	//     3  4  5     7
	//          2 1 6

	void Merge(int u, int v)
	{
		int uLeader = FindLeader(u);
		int vLeader = FindLeader(v);

		if(uLeader == vLeader)
			return;

		if (_rank[uLeader] > _rank[vLeader])
		{
			std::swap(uLeader, vLeader);
		}

		_parent[uLeader] = vLeader;

		if(_rank[uLeader] == _rank[vLeader])
			_rank[vLeader]++;
	}

private:
	vector<int> _parent;
	vector<int> _rank;
};

int main()
{

}