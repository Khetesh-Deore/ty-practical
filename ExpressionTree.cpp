#include <bits/stdc++.h>
using namespace std;
class node
{
public:
	char data;
	node *left;
	node *right;

	node(char d, node *l = NULL, node *r = NULL)
	{
		data = d;
		left = l;
		right = r;
	}
};

class expressionTree
{
	node *root;

public:
	node *tree(string prefix);
};

bool isoperator(char ch)
{
	return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

void print(node *root)
{
	if (!root)
		return;
	print(root->left);
	cout << root->data << " ";
	print(root->right);
}

node *expressionTree ::tree(string prefix)
{
	stack<node *> st;
	for (int i = prefix.size() - 1; i >= 0; i--)
	{
		node *newnode = new node(prefix[i]);
		if (isoperator(prefix[i]))
		{
			newnode->left = st.top();
			st.pop();
			newnode->right = st.top();
			st.pop();
		}
		st.push(newnode);
	}
	cout << "\nExpression Tree Constructed Successfully!\n";
	print(st.top());
	cout<<" and\n";
	return st.top();
}

void nonrecinorder(node *root)
{
	node *curr = root;
	stack<node *> st;
	while (curr != nullptr || !st.empty())
	{
		while (curr != nullptr)
		{
			st.push(curr);
			curr = curr->left;
		}
		curr = st.top();
		st.pop();
		cout << curr->data << " ";
		curr=curr->right;
	}
	cout << "\n";
}

void nonrecpreorder(node *root){
	stack<node *>st;
	st.push(root);
	while(!st.empty()){
		node * curr=st.top();
		st.pop();
		cout<<curr->data<<" ";
		if(curr->right){
			st.push(curr->right);
		}
		if(curr->left){
			st.push(curr->left);
		}
	}
}

void nonrecpostorder(node * root){
	stack<node *>s1,s2;
	s1.push(root);
	while(!s1.empty()){
		node * curr=s1.top();s1.pop();
		s2.push(curr);
		if(curr->left){
			s1.push(curr->left);
		}
		if(curr->right){
			s1.push(curr->right);
		}

	}
	while(!s2.empty()){
		node * curr=s2.top();s2.pop();
		cout<<curr->data<<" ";
	}
}

void mirror(node * root){
	node *mi=root;
	if(!mi)return;
	mirror(mi->left);
	mirror(mi->right);
	swap(mi->left,mi->right);
}

int main()
{
	expressionTree e;
	node *root = e.tree("+--a*bc/def");
	//nonrecinorder(root);
	//nonrecpreorder(root);
	nonrecpostorder(root);
	return 0;
}