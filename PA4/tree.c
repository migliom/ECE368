#include <stdlib.h>
#include <stdio.h>
#include "pa4.h"
#include "hbt.h"

Tnode *createNode(int key, char children)
{
	Tnode *node = malloc(sizeof(*node));
	node -> key = key;
	node -> balance = children;
	node -> left = NULL;
	node -> right = NULL;
	return node;
}

Tnode *inserTnode(Tnode *tn, int val)
{
		if(tn == NULL)
			return createNode(val, '1');

		if (val <= (tn -> key))
		{
			tn -> left = inserTnode(tn -> left, val);
		}

		else
		{
			tn -> right = inserTnode(tn -> right, val);
		}

		int balance = getBalance(tn);

		//case 2: if you insert to the left of the left child node 
		if(balance > 1 && (tn -> left -> key) >= val)
		{
			return clockRotation(tn);
		}

		//Case 2a: insert to the right of the left child
		else if(balance > 1 && (tn -> left -> key) < val)
		{
			tn -> left = counterClockRotation(tn -> left);
			return clockRotation(tn);
		}

		//case 2b: insert to the left of the right child
		else if(balance < -1 && (tn -> right -> key) > val)
		{
			tn -> right = clockRotation(tn -> right);
			return counterClockRotation(tn);
		}

		//Case 2c: insert to the right of the right child
		else if(balance < -1 && (tn -> right -> key) < val)
		{
			return counterClockRotation(tn);
		}

		return tn;
}
static Tnode *deleteHelper(Tnode *parent, Tnode *child, int *foundP)
{
	if(child -> right != NULL)
		child->right = deleteHelper(parent, child->right, foundP);
	
	(*foundP) = 1;
	if(child -> left != NULL && (*foundP))
	{
		Tnode *temp = child -> left;
		parent -> key = child -> key;
		free(child);
		(*foundP) = 0;
		return temp;
	}
	else if(child -> left == NULL && (*foundP))
	{
		(*foundP = 0);
		return NULL;
	}
}
static Tnode* immediatePredecessor(Tnode *tn)
{
	//recieves the node to be deleted
	int foundP = 0;
	return deleteHelper(tn, tn->right, &foundP);
}
	
Tnode *deleteNode(Tnode* tn, int val)
{
	if (tn == NULL) { return NULL; }

	if (val < (tn -> key))
	{
		tn -> left = deleteNode(tn -> left, val);
		return tn;
	}
	if (val > (tn -> key))
	{
		tn -> right = deleteNode(tn -> right, val);
		return tn;
	}
								// v is the same as tn ->  key 
	if (((tn ->  left) == NULL) && ((tn ->  right) == NULL))
	{
		free (tn);
		return NULL;
	}

	if ((tn ->  left) == NULL)
	{
		Tnode * temp = tn ->  right;
		free (tn);
		return temp;
	}

	if ((tn ->  right) == NULL)
	{
		Tnode * temp = tn -> left;        
		free (tn);
		return temp;
	}

	Tnode * immediateChild = tn -> left; 
	while ((immediateChild -> right) != NULL)
	{
		immediateChild = immediateChild -> right;
	} 
	
	tn ->  key = immediateChild -> key;
	immediateChild -> key = val;
	
	tn -> left = deleteNode(tn -> left, val);
	
	//if((tn->right) != NULL && (tn->left) != NULL)
	//	return (immediatePredecessor(tn));
	
	int nodeBalance = getBalance(tn);
	switch(nodeBalance)
	{
		case -2:	if(getBalance(tn->left) < 1)
								return clockRotation(tn);
							else{
								tn->left = counterClockRotation(tn->left);
								return clockRotation(tn);
							}
							break;
		case 2:	if(getBalance(tn->left) > -1)
								return counterClockRotation(tn);
							else{
								tn->right = clockRotation(tn->right);
								return counterClockRotation(tn);
							}
							break;
	}
	return tn;  
}

int getBalance(Tnode *tn)
{
	if(tn == NULL)
		return 0;
	return(height(tn -> left) - height(tn -> right));
}

Tnode *counterClockRotation(Tnode* tn)
{ 
	//Dr. Koh special
	Tnode *newRoot = tn -> right;
	Tnode *temp_ptr = newRoot -> left;
	newRoot -> left = tn;
	tn -> right = temp_ptr;
	return newRoot;
}

Tnode *clockRotation(Tnode* tn)
{	
	//Dr.Koh Special pt. 2
	Tnode *newRoot = tn -> left;
	Tnode *temp_ptr = newRoot -> right;
	newRoot -> right = tn;
	tn -> left = temp_ptr;
	return newRoot;
}

int max(int a, int b)
{
	if(a >= b)
		return a;
	else
		return b;
}

int height(Tnode *tn)
{	
	if(tn == NULL)
		return -1;
	return (1 + max(height(tn->left), height(tn->right)));
	
}

int checkBalance(Tnode *tn)
{

	if(tn == NULL)
		return 1;

	int leftHeight = height(tn -> left);
	int rightHeight = height(tn -> right);

		if(((leftHeight - rightHeight) > -2 && (leftHeight - rightHeight) < 2))
			if(checkBalance(tn -> right) && checkBalance(tn -> left))
				return 1;
	
	return 0;

}

void deleteTree(Tnode* root)
{
	if(root == NULL)
		return;
	deleteTree(root -> left);
	deleteTree(root -> right);
	free(root);
}

