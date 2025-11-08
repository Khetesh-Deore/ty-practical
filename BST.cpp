#include <bits/stdc++.h>
using namespace std;
class node
{
public:
	int data;
	node *left;
	node *right;

	node(int d, node *l = NULL, node *r = NULL)
	{
		data = d;
		left = l;
		right = r;
	}
};

class bst
{
	node *root;

public:
	node *insert(int data, node *root);
	void print(node *root);
	void reverseprint(node *root);
	void minn(node *root);
	int height(node *root);
	void search(node *root, int target);
};

node *bst::insert(int data, node *root)
{
	if (!root)
	{
		node *newnode = new node(data);
		return newnode;
	}
	if (root->data < data)
	{
		root->right = insert(data, root->right);
	}
	else
	{
		root->left = insert(data, root->left);
	}
	return root;
}

void bst ::print(node *root)
{
	if (!root)
		return;
	print(root->left);
	cout << root->data << " ";
	print(root->right);
}

void bst ::reverseprint(node *root)
{
	if (!root)
		return;
	reverseprint(root->right);
	cout << root->data << " ";
	reverseprint(root->left);
}
int bst ::height(node *root)
{
	if (!root)
		return 0;
	int lh = height(root->left);
	int rh = height(root->right);
	return 1 + max(lh, rh);
}

void bst::minn(node *root)
{
	if (!root)
	{
		cout << -1;
		return;
	}
	while (root && root->left)
	{
		root = root->left;
	}
	cout << "\nMin:" << root->data;
}
void bst::search(node *root, int target)
{
	if (!root)
	{
		cout << "\nTarget Not  found ";
		return;
	}

	if (root->data == target)
	{
		cout << "\nElement found";
		return;
	}
	else if (root->data < target)
		search(root->right, target);
	else
		search(root->left, target);
}

int main()
{
	bst b;
	node *root = b.insert(5, NULL);
	root = b.insert(6, root);
	root = b.insert(9, root);
	root = b.insert(4, root);
	root = b.insert(11, root);
	root = b.insert(10, root);
	b.print(root);
	b.minn(root);
	cout << "\nheight:" << b.height(root);
	b.search(root, 9);
	b.search(root, 7);
	b.reverseprint(root);
}
