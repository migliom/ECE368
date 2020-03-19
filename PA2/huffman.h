#ifndef __HUFFMAN__
#define __HUFFMAN__

//typedef struct{
//	char value;
//	unsigned long frequency;
//}charFrequency;

typedef struct treenode{
  struct treenode *left, *right;
  unsigned char value;
  unsigned long freq;
}treeNode;

typedef struct list{
  struct list *next;
  treeNode * treePoint;
}listNode;

unsigned long *findFreq(char *filename, unsigned long *counterDecomp);
listNode *buildLinked(unsigned long *arr, int size);
void MergeSort(listNode ** ln);
listNode *buildHuff(listNode *sortedList);
int writeCount(char *filename, unsigned long *arr);

int writeTree(char *filename, treeNode *tn);

int **codeBook(listNode *ln, int *row, int *col);

void writeCode(char *outputFile, int **arr, int row, int col, treeNode *tn, int *preOrder);
void compressFile(char *input, char *output, int **codebook, treeNode *tn, unsigned long size);
void destory(treeNode *tn);
#endif

