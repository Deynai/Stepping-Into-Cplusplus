#pragma once
#include <iostream>

struct node
{
	int value;
	node* left;
	node* right;
};

node* add_node(node* p_tree, int number)
{
	// Base case, when we have reached the end of the tree and have an empty node, add our value.
	if (p_tree == NULL)
	{
		node* p_new = new node;
		p_new->value = number;
		p_new->left = NULL;
		p_new->right = NULL;
		return p_new;
	}

	// Decide whether to go left or right. Left for smaller numbers, right for larger numbers. 
	if (number <= p_tree->value)
	{
		p_tree->left = add_node(p_tree->left, number);
	}
	else
	{
		p_tree->right = add_node(p_tree->right, number);
	}
	return p_tree;
}

node* find_least(node* p_tree, int &smallest)
{
	if (p_tree->left == NULL)
	{
		smallest = p_tree->value;
		return p_tree->right;
	}
	else
	{
		p_tree->left = find_least(p_tree->left, smallest);
	}
	return p_tree;
}

node* deleteNode(node* p_tree, int number)
{
	if (p_tree == NULL)
	{
		return p_tree;
	}

	if (p_tree->value == number)
	{
		// 3 CASES:

		// case 1: no children
		if (p_tree->left == NULL && p_tree->right == NULL)
		{
			return NULL;
		}
		// case 2: one child
		if (p_tree->left == NULL && p_tree->right != NULL)
		{
			node* p_tree_right = p_tree->right;
			delete p_tree;
			return p_tree_right;
		}

		if (p_tree->left != NULL && p_tree->right == NULL)
		{
			node* p_tree_left = p_tree->left;
			delete p_tree;
			return p_tree_left;
		}
		// case 3: two children

		else
		{
			int smallest = 0;
			// find the smallest number on the right hand side of the tree, we are going to replace the node we want to delete with that value, and then delete the node that contained the least value from the right side of the tree.
			// note this is guaranteed to be either a zero or one child case. 
			p_tree->right = find_least(p_tree->right, smallest);
			p_tree->value = smallest;
			return p_tree;
		}
	}

	if (p_tree->value > number)
	{
		p_tree->left = deleteNode(p_tree->left, number);
	}
	else
	{
		p_tree->right = deleteNode(p_tree->right, number);
	}
	return p_tree;
}

void deleteTree(node* p_tree)
{
	if (p_tree != NULL)
	{
		deleteTree(p_tree->left);
		deleteTree(p_tree->right);
		delete p_tree;
	}
	return;
}

node* searchTree(node* p_tree, int number)
{
	if (p_tree == NULL)
	{
		return NULL;
	}

	if (p_tree->value == number)
	{
		return p_tree;
	}

	if (p_tree->value > number)
	{
		p_tree = searchTree(p_tree->left, number);
	}

	else
	{
		p_tree = searchTree(p_tree->right, number);
	}

	return p_tree;
}