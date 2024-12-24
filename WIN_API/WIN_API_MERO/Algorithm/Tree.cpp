#include <queue>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

using namespace std;

// - 선형자료구조   : 
//  - vector
//  - list
//  - queue
//  - stack
// 
// - 비선형자료구조 :
//  - graph
//	- tree(map)
//	- unordered_map(hash_table)

// Tree
// 1. 계층구조를 설명하기 좋은 구조
//  - 부모노드와 자식노드로 이루어져있는 구조
// => 모든 트리에는 최상위 부모노드가 단 하나 있다. (Root 노드)
// => 모든 트리에는 여러명의 최하위 노드가 있다. (Leaf 노드)
// 
// 2. 트리는 잘라도 트리다.
// => 서브트리가 존재한다.
// => 재귀적으로 자식을 타고 들어갈 수 있다.

// 트리
// 1. 이진트리
// 2. 포화이진트리
// 3. 완전이진트리
// 4. 힙트리
// 5. 자가균형이진탐색트리

struct Node
{
	Node() {}
	Node(const string& data) : data(data) {}

	vector<Node*> children;
	string data;
};

Node* CreateTree()
{
	Node* root = new Node("개발부");
	{
		Node* node1 = new Node("프로그래밍팀");
		root->children.push_back(node1);
		{
			Node* node1_1 = new Node("서버");
			node1->children.push_back(node1_1);

			Node* node1_2 = new Node("클라이언트");
			node1->children.push_back(node1_2);

			Node* node1_3 = new Node("엔진");
			node1->children.push_back(node1_3);
		}

		Node* node2 = new Node("기획팀");
		root->children.push_back(node2);
		{
			Node* node1_1 = new Node("스토리");
			node2->children.push_back(node1_1);

			Node* node1_2 = new Node("시스템");
			node2->children.push_back(node1_2);

			Node* node1_3 = new Node("레벨디자인");
			node2->children.push_back(node1_3);
		}

		Node* node3 = new Node("아트팀");
		root->children.push_back(node3);
		{
			Node* node1_1 = new Node("배경");
			node3->children.push_back(node1_1);

			Node* node1_2 = new Node("원화");
			node3->children.push_back(node1_2);

			Node* node1_3 = new Node("모델");
			node3->children.push_back(node1_3);
		}
	}

	return root;
}

// Tree 순회
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