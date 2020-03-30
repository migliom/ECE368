#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "hbt.h"
#include "pa4.h"
static Tnode *inserTnode_e(Tnode *tn, int val, char children, char prevChar, int *isBST)
{
		if(tn == NULL)
			return createNode(val, children);
		
		prevChar = tn -> balance;
		if (val <= (tn -> key))
		{
			tn -> left = inserTnode_e(tn -> left, val, children, prevChar, isBST);
			if(prevChar != 2 && prevChar != 3)
				((*isBST) = 0);
		}
		else 
		{
			tn -> right = inserTnode_e(tn -> right, val, children, prevChar, isBST);
			if((prevChar) != 1 && (prevChar != 3))
				((*isBST = 0));
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
	long check = 0;
	int counter = 0;
	Tnode *tn = NULL;
	
	while(!feof(fptr))
	{
		check = fread(&temp, sizeof(int), 1, fptr);
		++counter;
	}
	temp = fseek(fptr, 0, SEEK_SET);
	for(int i = 0; i < (counter - 3); i++)
	{
		check = fread(&temp, sizeof(int), 1, fptr);
		check = fread(&childCount, sizeof(char), 1, fptr);
		tn = inserTnode_e(tn, temp, childCount, '0', isBST);
	}
	
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

	long check = 0;
	int temp = 0;
	int counter = 0;
	char operationType = 0;

	while(!feof(fptr))
	{
		check = fread(&temp, sizeof(int), 1, fptr);
		++counter;
	}

	temp = fseek(fptr, 0, SEEK_SET);

	Tnode *tn = NULL;
	for(int i = 0; i < (counter - 3); i++)
	{
		check = fread(&temp, sizeof(int), 1, fptr);
		check = fread(&operationType, sizeof(char), 1, fptr);

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
	fprintf(stdout, "%d\n", tn->key);
	if(tn -> left != NULL && tn -> right == NULL){
		children = 2;
		fwrite(&children, 1, sizeof(char), fptr);
	}
	else if(tn -> right != NULL && tn -> left == NULL){
		children = 1;
		fwrite(&children, 1, sizeof(char), fptr);
	}
	else if(tn -> right != NULL && tn -> left != NULL){
		children = 3;
		fwrite(&children, 1, sizeof(char), fptr);
	}
	else
		fwrite(&children, 1, sizeof(char), fptr);
	
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

	
