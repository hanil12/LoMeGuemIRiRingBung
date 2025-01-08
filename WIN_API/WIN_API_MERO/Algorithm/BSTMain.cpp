#include <queue>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

using namespace std;

#include "BinarySearchTree.h"

int main()
{
	BinarySearchTree tree;
	tree.Insert(100);
	tree.Insert(50);
	tree.Insert(150);
	tree.Insert(25);
	tree.Insert(70);
	tree.Insert(120);
	tree.Insert(170);

	tree.PrintTree(tree.root);

	Node* temp = tree.Search(tree.root, 70);
	cout << temp->key << endl;;

	return 0;
}