#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "hbt.h"

Tnode *readCheckFile(char *, int *isBST, int *isBalanced);
Tnode *readOperationsFile(char*, int*);
void printToFile(char*, Tnode*);

Tnode *createNode(int, char);
Tnode *insertNode(Tnode*, int);
Tnode * deleteNode(Tnode*, int);

int max(int, int);
int height(Tnode*);
int getBalance(Tnode *tn);
Tnode *counterClockRotation(Tnode*);
Tnode *clockRotation(Tnode*);
int checkBalance(Tnode*);


void deleteTree(Tnode*);
	
