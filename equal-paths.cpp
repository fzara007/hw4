#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)
#include <iostream>
#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
int height(Node *root);

bool equalPaths(Node * root)
{
	// Add your code below
	if(height(root)==0 || height(root)==1) return true;
	if(height(root->left)==0) return equalPaths(root->right);
	if(height(root->right)==0) return equalPaths(root->left);
	if(height(root->left)!=height(root->right)) return false;
	return equalPaths(root->left) && equalPaths(root->right);
}


int height(Node *root) {
	int res = 1;
	if(root==NULL) return 0;

	res += height(root ->left);
	int h = height(root ->right)+1;
	if(h>res) res = h;
	
	return res;
}