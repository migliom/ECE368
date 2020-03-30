#include <stdlib.h>
#include <stdio.h>
#include "pa4.h"
#include "hbt.h"

int main(int argc, char **argv)
{
	if(argc < 3)
		return EXIT_FAILURE;
	
	if(argv[1][1] == 'e')
	{
		int isBST = 1;
		int isBalanced = 0;
		Tnode *tn = NULL;
		tn = readCheckFile(argv[2], &isBST, &isBalanced);
		if(tn == NULL){
			fprintf(stdout, "%d,%d,%d\n", 0,0,0);
			return EXIT_FAILURE;
		}
		
		else
			fprintf(stdout, "%d,%d,%d\n", 1, isBST, isBalanced);

		deleteTree(tn);
		return EXIT_SUCCESS;
	}

	if(argv[1][1] == 'b')
	{
		int fileCheck;
		Tnode *root = NULL;
		root = readOperationsFile(argv[2], &fileCheck);

		if(fileCheck == -1){
			fprintf(stdout, "%d\n", fileCheck);
			return EXIT_FAILURE;
		}
		fprintf(stdout, "%d\n", fileCheck);
		printToFile(argv[3], root);
		deleteTree(root);
	}

	return EXIT_SUCCESS;
}
