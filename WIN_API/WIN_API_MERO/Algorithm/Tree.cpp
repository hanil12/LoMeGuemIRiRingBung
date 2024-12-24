#include <queue>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

using namespace std;

// - �����ڷᱸ��   : 
//  - vector
//  - list
//  - queue
//  - stack
// 
// - �����ڷᱸ�� :
//  - graph
//	- tree(map)
//	- unordered_map(hash_table)

// Tree
// 1. ���������� �����ϱ� ���� ����
//  - �θ���� �ڽĳ��� �̷�����ִ� ����
// => ��� Ʈ������ �ֻ��� �θ��尡 �� �ϳ� �ִ�. (Root ���)
// => ��� Ʈ������ �������� ������ ��尡 �ִ�. (Leaf ���)
// 
// 2. Ʈ���� �߶� Ʈ����.
// => ����Ʈ���� �����Ѵ�.
// => ��������� �ڽ��� Ÿ�� �� �� �ִ�.

// Ʈ��
// 1. ����Ʈ��
// 2. ��ȭ����Ʈ��
// 3. ��������Ʈ��
// 4. ��Ʈ��
// 5. �ڰ���������Ž��Ʈ��

struct Node
{
	Node() {}
	Node(const string& data) : data(data) {}

	vector<Node*> children;
	string data;
};

Node* CreateTree()
{
	Node* root = new Node("���ߺ�");
	{
		Node* node1 = new Node("���α׷�����");
		root->children.push_back(node1);
		{
			Node* node1_1 = new Node("����");
			node1->children.push_back(node1_1);

			Node* node1_2 = new Node("Ŭ���̾�Ʈ");
			node1->children.push_back(node1_2);

			Node* node1_3 = new Node("����");
			node1->children.push_back(node1_3);
		}

		Node* node2 = new Node("��ȹ��");
		root->children.push_back(node2);
		{
			Node* node1_1 = new Node("���丮");
			node2->children.push_back(node1_1);

			Node* node1_2 = new Node("�ý���");
			node2->children.push_back(node1_2);

			Node* node1_3 = new Node("����������");
			node2->children.push_back(node1_3);
		}

		Node* node3 = new Node("��Ʈ��");
		root->children.push_back(node3);
		{
			Node* node1_1 = new Node("���");
			node3->children.push_back(node1_1);

			Node* node1_2 = new Node("��ȭ");
			node3->children.push_back(node1_2);

			Node* node1_3 = new Node("��");
			node3->children.push_back(node1_3);
		}
	}

	return root;
}

// Tree ��ȸ
void PrintTree(Node* node, int depth = 0)
{
	for (int i = 0; i < depth; i++)
	{
		cout <<"-";
	}

	cout << node->data << endl;
	for (auto child : node->children)
	{
		PrintTree(child, depth + 1);
	}
}

int main()
{
	Node* developeTeam = CreateTree();
	PrintTree(developeTeam);


	return 0;
}