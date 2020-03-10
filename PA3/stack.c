#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "pa3.h"

void createTreeNode(listNode ** lnode)
{
	treeNode *tnode = malloc(sizeof(treeNode));
	if(tnode == NULL){
			fputs(stderr, "Program ran out of memory\0");
			return;
	}
	tnode -> right = NULL;
	tnode -> left = NULL;
	(*lnode) -> treepoint = tnode;
}

listNode *push(listNode* lnode, char str[])
{
	listNode *p = NULL;
	p = malloc(sizeof(listNode));
	if(p == NULL){
			fputs(stdout, "Program ran out of memory\0");
			return;
	}
	createTreeNode(&p);
	//pushing values into the stack
	char division = '$';
	int boxNumber = 0;
	int x = 0;
	int y = 0;
	int height = 0;
	int width = 0;

	if(str[0] == 'V' ||  str[0] == 'H'){
		division = str[0];
	}
	else
		sscanf(str,"%d(%d,%d)\n",&boxNumber, &x, &y); 	
	
		height = y;
		width = x;
		p -> treepoint -> boxNum = boxNumber;
		p -> treepoint -> division = division;
		p -> treepoint -> x = x;
		p -> treepoint -> y = y;
		p -> treepoint -> width = width;
		p -> treepoint -> height = height;
		p -> treepoint -> finalX = -1;
		p -> treepoint -> finalY = -1;
	p -> next = (lnode);
	return p;
}
static int max(int leftVal, int rightVal) //find max of the two tree values
{
  if(leftVal >= rightVal)
		return leftVal;
	else{
		return rightVal;
	}
}

bool pop(listNode ** lnode) //popping the nodes to make tree
{
  if(((*lnode) -> treepoint -> division) > 65)
	{
		listNode *p = (*lnode) -> next;
		if(p == NULL)
			return false; //if this is false there aren't enough nodes to pop
		listNode *q = (*lnode) -> next -> next;
		if(q == NULL)
			return false;
		listNode *temp = q -> next; //sets temp = to list next so we dont lose the rest of the list

		((*lnode) -> treepoint -> right) = (p -> treepoint); //building tree
		((*lnode) -> treepoint -> left) = (q -> treepoint); //building tree

		if((*lnode) -> treepoint -> division == 'V'){ //checking if division is a vertical cut
			((*lnode) -> treepoint -> width) = (p -> treepoint -> width) + (q -> treepoint -> width); //sum the widths 
			((*lnode) -> treepoint -> height) = max((p -> treepoint -> height), (q -> treepoint -> height)); //take max of the heights
		}
		else if((*lnode) -> treepoint -> division ==  'H'){ //checking to see if horizontal cut
			(*lnode) -> treepoint -> height = (p -> treepoint -> height) + (q -> treepoint -> height); //sum the heights
			(*lnode) -> treepoint -> width = max((p -> treepoint -> width), (q -> treepoint -> width)); //find max of width
		}
	
		(*lnode) -> next = temp;
		free(q);
		free(p);
		return true;
	}
}


