#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct _treeNode{
	int boxNum;
	int x;
	int y;
	int height;
	int width;
	char division;
	struct _treeNode *left, *right;
	int finalX;
	int finalY;
}treeNode;

typedef struct _listNode{
	treeNode *treepoint;
	struct _listNode *next;
}listNode;


listNode *readFromFile(char * filename);
listNode* push(listNode *lnode, char arr[]);
bool pop(listNode **lnode);
void createTreeNode(listNode **lnode);
void preOrderPrint(char *filename, listNode *ln);
void printToFile(char *filename, listNode *ln);
void freetree(treeNode *tn);
void packing(char *filename, treeNode *tn);
