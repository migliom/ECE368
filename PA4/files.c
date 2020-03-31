#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "hbt.h"
#include "pa4.h"
static int checkInorder(Tnode *tn)
{
	if(tn == NULL)
		return 1;
	if(tn->left != NULL && !(tn->left->key <= tn->key))
		return 0;
	if(tn->right != NULL && !(tn->right->key >= tn->key))
		return 0;

	if(!checkInorder(tn->left) || !checkInorder(tn->right))
		return 0;

	return 1;
	/*if(tn == NULL)
		return;
	fprintf(stdout, "%d\n",tn->key);
	checkInorder(tn->left);
	checkInorder(tn->right);
	return 95;*/
}
static Tnode *inserTnode_e(FILE *fptr)
{	
	int val = 0;
	int children = 0;
	fread(&val, sizeof(int), 1, fptr);
	fread(&children, sizeof(char), 1, fptr);
	
	Tnode *tn = createNode(val, children);
	switch(children)
	{
		case 0:
			tn->right = NULL;
			tn->left = NULL;
			break;

		case 1: 
			tn->left = NULL;
			tn->right = inserTnode_e(fptr);
			break;
	
		case 2:
			tn->right = NULL;
			tn->left = inserTnode_e(fptr);
			break;

		case 3:
			tn->left = inserTnode_e(fptr);
			tn->right = inserTnode_e(fptr);
			break;
	}
	return tn;
}


Tnode *readCheckFile(char * filename, int *isBST, int *isBalanced)
{
	FILE *fptr = fopen(filename, "rb");
	if(fptr == NULL)
	{
		return NULL;
	}

	char childCount = 0;
	int temp = 0;
	Tnode *tn = inserTnode_e(fptr);

	int checkInorderVal = INT_MIN;
	(*isBST) = checkInorder(tn);
	fclose(fptr);
	(*isBalanced) = checkBalance(tn);
	return tn;
}
//----------------------------------------------------------------//
//----------------------------------------------------------------//

Tnode *readOperationsFile(char *filename, int *fileCheck)
{
	FILE *fptr = fopen(filename, "rb");
	if(fptr == NULL)
	{
		(*fileCheck = -1);
		return NULL;
	}

	int temp = 0;
	char operationType = 0;

	Tnode *tn = NULL;
	while((fread(&temp, sizeof(int), 1, fptr)) != 0){
		fread(&operationType, sizeof(char), 1, fptr);
	//have check
		if(operationType == 'i')
			tn = inserTnode(tn, temp);

		else if(operationType == 'd')
			tn = deleteNode(tn, temp);

		else
		{
			(*fileCheck = 0);
			fclose(fptr);
			return tn;
		}
	}
	(*fileCheck) = 1;
	fclose(fptr);
	return tn;
}
static void printToFileHelper(FILE *fptr, Tnode *tn)
{
	if(tn == NULL)
		return;

	int children = 0;
	fwrite(&(tn->key),1, sizeof(int), fptr);
	//fprintf(stdout, "%d", tn->key);
	if(tn -> left != NULL && tn -> right == NULL){
		children = 2;
		fwrite(&children, 1, sizeof(char), fptr);
		//fprintf(stdout, " %d\n", 2);

	}
	else if(tn -> right != NULL && tn -> left == NULL){
		children = 1;
		fwrite(&children, 1, sizeof(char), fptr);
		//fprintf(stdout, " %d\n", 1);

	}
	else if(tn -> right != NULL && tn -> left != NULL){
		children = 3;
		fwrite(&children, 1, sizeof(char), fptr);
		//fprintf(stdout, " %d\n", 3);

	}
	else{
		fwrite(&children, 1, sizeof(char), fptr);
		//fprintf(stdout, " %d\n", 0);
	}
	printToFileHelper(fptr, tn -> left);
	printToFileHelper(fptr, tn -> right);
}
void printToFile(char *filename, Tnode *tn)
{
	FILE *fptr = fopen(filename, "wb");
	printToFileHelper(fptr, tn);
	fclose(fptr);
	return;
}

	
