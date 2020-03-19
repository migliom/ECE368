#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "huffman.h"

int main(int argc, char **argv)
{
  if(argc != 6)
  {
    return EXIT_FAILURE;
  }
  unsigned long totDecomp = 0;
  unsigned long *arr = findFreq(argv[1], &totDecomp);

  if(arr == NULL)
  {
    return EXIT_FAILURE;
  }
  int arrLen = writeCount(argv[2], arr);
  if(arrLen == 0)
    return EXIT_FAILURE;
  listNode *ln = NULL; //malloc(sizeof(treeNode));
  ln = buildLinked(arr, arrLen);
  if(ln == NULL)
    return EXIT_FAILURE;
  mergeSort(&ln);
  free(arr);
  int size = 0;
  int writeCounter = 0;
  listNode *lCount = ln;
  while(lCount != NULL)
  {
    ++size;
    lCount = lCount -> next;
  }
  listNode *Ln = buildHuff(ln);  //build the huffman tree pointed to by ln
  int charArraySize = ((size*2)+(size-1));
  char *charArr[charArraySize + 1]; //create array to store preorder traversal values 
  for(int ind1 = 0; ind1 < charArraySize + 1; ind1++)
  {
    charArr[ind1] = 0;
  }
  writeTree(argv[3], (Ln->treePoint), &writeCounter, charArr); //write tree file
  for(int temp1 = 0; temp1 < (charArraySize); temp1++)
  {
    printf("%c", charArr[temp1]);
  }
  int row = 0;
  int col = 0;
  int **codeTable = codeBook(Ln, &row, &col); //in this program we free ln and create 2D array
  if(codeTable == NULL)
    return EXIT_FAILURE;
  int rowNum = 256;
  int *preOrder = malloc(size * sizeof(int));
  writeCode(argv[4], codeTable, row, col, Ln->treePoint, preOrder);
  compressFile(argv[1], argv[5], codeTable, rowNum, col, Ln->treePoint, totDecomp, charArraySize, size);
  for(int i = 0; i < rowNum; i++)
  {
    int *currentArr = codeTable[i];
    free(currentArr);
  }
  free(preOrder);
  destroy(Ln->treePoint);
  free(Ln);
  free(codeTable);
}
