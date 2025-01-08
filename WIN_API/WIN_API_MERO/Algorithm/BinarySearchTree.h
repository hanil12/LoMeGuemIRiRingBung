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

	int key = -1; // key�� �������� ����
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

			// �ڸ� ã��, �θ� ã��
			while (true)
			{
				// ���� ������ �ٻ�� ����̸� break
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

			// �θ� ã������ �����ڽ����� ������, ������ �ڽ����� ������
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

		// Tree�� ������ȸ : Root - ���� �ڽĵ� - �������ڽĵ�
		// Tree�� ������ȸ : ���� �ڽĵ� - Root - �������ڽĵ�
		// Tree�� ������ȸ : �������ڽĵ� - Root - ���� �ڽĵ�
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
	Node* Previous(Node* node) // �ش� ����� key���� ��ĭ �� ���� ��
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

	// delete �Լ�
	void Replace(Node* node1, Node* node2)
	{
		if (node1->parent == nullptr)
			root = node2;

		// node1�� �θ��ʿ��� ���ʿ� �ִ� �ڽ��̳�?
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