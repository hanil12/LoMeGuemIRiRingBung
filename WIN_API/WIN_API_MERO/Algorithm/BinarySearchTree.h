#pragma once

#include <iostream>

using namespace std;

struct Node
{
	Node() {}
	Node(int key) : key(key) {}

	Node* left = nullptr;
	Node* right = nullptr;
	Node* parent = nullptr;

	int key = -1; // key를 기준으로 정렬
	int data = 0;
};

class BinarySearchTree
{
public:
	BinarySearchTree() {}
	~BinarySearchTree() {}

	void Insert(int key)
	{
		{
			Node* newNode = new Node(key);

			if (root == nullptr)
			{
				root = newNode;
				return;
			}

			Node* node = root;
			Node* parent = nullptr;

			// 자리 찾기, 부모 찾기
			while (true)
			{
				// 현재 마지막 잎사귀 노드이면 break
				if (node == nullptr)
					break;

				parent = node;
				if (key < node->key)
				{
					node = node->left;
				}
				else
				{
					node = node->right;
				}
			}

			// 부모를 찾았으면 왼쪽자식으로 붙을지, 오른쪽 자식으로 붙을지
			newNode->parent = parent;
			if (key < parent->key)
			{
				parent->left = newNode;
			}
			else
			{
				parent->right = newNode;
			}
		}
	}
	void PrintTree(Node* node)
	{
		if (node == nullptr)
			return;

		// Tree의 전위순회 : Root - 왼쪽 자식들 - 오른쪽자식들
		// Tree의 전위순회 : 왼쪽 자식들 - Root - 오른쪽자식들
		// Tree의 전위순회 : 오른쪽자식들 - Root - 왼쪽 자식들
		PrintTree(node->left);
		cout << node->key << endl;
		PrintTree(node->right);
	}
	Node* Search(Node* node, int key)
	{
		if (node == nullptr)
			return nullptr;

		if (key == node->key)
			return node;

		if (key < node->key)
			return Search(node->left, key);
		else
			return Search(node->right, key);

		return nullptr;
	}
	Node* Min(Node* node)
	{
		if (node == nullptr)
			return nullptr;

		if (node->left != nullptr)
			return Min(node->left);

		return node;
	}
	Node* Max(Node* node)
	{
		if (node == nullptr)
			return nullptr;

		if (node->right != nullptr)
			return Max(node->right);

		return node;
	}
	Node* Previous(Node* node) // 해당 노드의 key보다 한칸 더 작은 얘
	{
		if (node == nullptr)
			return nullptr;

		if (node->left == nullptr)
			return nullptr;

		return Max(node->left);
	}
	Node* Next(Node* node)
	{
		if (node == nullptr)
			return nullptr;

		if (node->right == nullptr)
			return nullptr;

		return Min(node->right);
	}

	void Delete(Node* node)
	{
		if(node == nullptr)
			return;

		if (node->left == nullptr && node->right == nullptr)
		{
			if (node == root)
			{
				root = nullptr;
				delete node;
				return;
			}

			if(node->parent->left == node)
				node->parent->left = nullptr;
			else
				node->parent->right = nullptr;

			delete node;
		}
		else if (node->left == nullptr)
		{
			Replace(node, node->right);
		}
		else if (node->right == nullptr)
		{
			Replace(node, node->left);
		}
		else
		{
			Node* prev = Previous(node);
			node->key = prev->key;
			node->data = prev->data;

			Delete(prev);
		}
	}

	Node* root = nullptr;
private:

	// delete 함수
	void Replace(Node* node1, Node* node2)
	{
		if (node1->parent == nullptr)
			root = node2;

		// node1이 부모쪽에서 왼쪽에 있는 자식이냐?
		else if (node1 == node1->parent->left)
		{
			node1->parent->left = node2;
		}
		else
		{
			node1->parent->right = node2;
		}

		if (node2 != nullptr)
			node2->parent = node1->parent;

		delete node1;
	}
};