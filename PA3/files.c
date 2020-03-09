#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "pa3.h"
#define MAX_SIZE 35 //max size of a line: max size of an integer is 10 digits
listNode *readFromFile(char * filename)
{
	FILE *fptr = fopen(filename, "r");
	if(fptr == NULL){
		fclose(fptr);
		return NULL;
	}
	listNode *head = malloc(sizeof(listNode));
	if(head == NULL){
		fputs(stdout, "No memory in the program");
		return NULL;
	}

	char arr[MAX_SIZE];
	for(int i = 0; i < MAX_SIZE; i++)
	{
		arr[i] = 0;
	}
	//memset(arr[0], 0, sizeof(arr));
	char division = '$';
	int boxNumber = 0;
	int x = 0;
	int y = 0;
	int height = 0;
	int width = 0;
	fgets(arr, MAX_SIZE, fptr);
	if(arr[0] == 'V' ||  arr[0] == 'H')
		division = arr[0];
	else
		sscanf(arr,"%d(%d,%d)\n",&boxNumber, &x, &y); 
	
	height = y;
	width = x;
	createTreeNode(&head);
	head -> treepoint -> boxNum = boxNumber;
	head -> treepoint -> division = division;
	head -> treepoint -> x = x;
	head -> treepoint -> y = y;
	head -> treepoint -> width = width;
	head -> treepoint -> height = height;
	head -> treepoint -> finalX = -1;
	head -> treepoint -> finalY = -1;

	while(fgets(arr, MAX_SIZE, fptr))
	{
		head = push(head, arr);
		bool temp = pop(&head);
	}
	fclose(fptr);
	return head;
}
/*\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
static void preOrderHelper(FILE **fptr, treeNode *tn)
{
	if(tn == NULL)
		return;
	if((tn -> division == 'H') || (tn -> division == 'V'))
	{
		fprintf((*fptr), "%c\n", tn -> division);
	}
	else 
	{
		int x = tn -> x;
		int y = tn -> y;
		int boxNum = tn -> boxNum;
		fprintf((*fptr), "%d(%d,%d)\n",boxNum, x, y);
	}
	(preOrderHelper(fptr, tn -> left));
	(preOrderHelper(fptr, tn -> right));
}
void preOrderPrint(char *filename, listNode *lnode)
{
	FILE *fptr = fopen(filename, "w");
	if(fptr == NULL)
	{
		fclose(fptr);
		return;
	}
	treeNode *tn = lnode -> treepoint;
	if(tn == NULL)
	{
		fclose(fptr);
		return;
	}
	preOrderHelper(&fptr, tn); 
	fclose(fptr);
}
/*\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
static void printToFileHelper(FILE **fptr, treeNode *tn)
{
	if(tn == NULL)
		return;
	(printToFileHelper(fptr, tn -> left));
	(printToFileHelper(fptr, tn -> right));
  if((tn -> division == 'H') || (tn -> division == 'V'))
	{
		char division = tn -> division;
		int height = tn -> height;
		int width = tn -> width;
		fprintf((*fptr), "%c(%d,%d)\n", division, width, height);
	}
	else 
	{
		int x = tn -> x;
		int y = tn -> y;
		int boxNum = tn -> boxNum;
		fprintf((*fptr), "%d(%d,%d)\n",boxNum, x, y);
	}
}
void printToFile(char *filename, listNode *lnode)
{
	FILE *fptr = fopen(filename, "w");
	if(fptr == NULL)
	{
		fclose(fptr);
		return;
	}
	treeNode *tn = lnode -> treepoint;
	if(tn == NULL)
	{
		fclose(fptr);
		return;
	}
	printToFileHelper(&fptr, tn); 
	fclose(fptr);
}
/*///////////////////////////////////////\*/
static void packingHelper1(FILE *fptr, treeNode *tn)
{
	if(tn == NULL)
		return;
	packingHelper1(fptr, tn->left);
	packingHelper1(fptr, tn->right);
	if(tn -> division == '$')
	{
		int width = tn -> width;
		int height = tn -> height;
		int boxNum = tn -> boxNum;
		int x = tn -> finalX;
		int y = tn -> finalY;
		fprintf(fptr, "%d((%d,%d)(%d,%d))\n",boxNum, width, height, x, y);
	}

}
static void packingHelper2(treeNode *tn, int xCoordinate, int yCoordinate)
{
	
	if((tn) == NULL)
	{
		return;
	}
	// if node == 'H'
	// packingHelper2(right, int xCoord, int Ycoord
	// packingHelper2(left, xCoord, (Ycoord + right -> height))
	//
	// if node == 'V'
	// packingHelper2(left, int xCoord, int Ycoord
	// packingHelper2(right, (Xcoord + left -> width), y)
	// 
	// if node == $
	// node -> finalX = xCoord
	// node -> finalY = yCoord
	//
	// return;
	treeNode *left = tn -> left;
	treeNode *right = tn -> right;

	switch (tn -> division)
	{
		//change coordinates 
		case 'H':	packingHelper2(right, xCoordinate, yCoordinate);
							packingHelper2(left, xCoordinate, (yCoordinate + (right -> height)));
							break;

		case 'V': packingHelper2(left, xCoordinate, yCoordinate);
							packingHelper2(right, (xCoordinate + (left -> width)), yCoordinate);
							break;

		case '$': tn -> finalX = xCoordinate;
							tn -> finalY = yCoordinate;
							break;
	}
	return;
}
void packing(char *filename, treeNode *tn)
{
	FILE *fptr = fopen(filename, "w");
	packingHelper2(tn, 0, 0);
	packingHelper1(fptr, tn);
	fclose(fptr);
	return;
}
static void deleteTreeNode(treeNode *tr)
{
	if(tr == NULL)
		return;
	deleteTreeNode(tr->left);
	deleteTreeNode(tr->right);
	free(tr);
}
void freeTree(treeNode *tr)
{
	if(tr == NULL)
		return;
	deleteTreeNode(tr);
}
