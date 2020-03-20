#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "pa3.h"

int main(int argc, char ** argv)
{
	if(argc != 5){
		return EXIT_FAILURE;
	}
	listNode *head = readFromFile(argv[1]);
	if(head == NULL)
		return;
	preOrderPrint(argv[2], head);
	printToFile(argv[3], head);
	packing(argv[4], head->treepoint);
	freeTree(head->treepoint);
	free(head);
	return EXIT_SUCCESS;
}
