#include "huffman.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <math.h>

unsigned long *findFreq(char *filename, unsigned long*counter)
{
  unsigned long asciiLen = 256;
  unsigned long *arr;
  arr = malloc((asciiLen) *sizeof(unsigned long)); //allocate enough memory for all ascii values
  for(int ind1=0;ind1<asciiLen;ind1++)
  {
    arr[ind1] = 0;
  }
  FILE *fptr = fopen(filename, "r");
  if(fptr == NULL)
  {
    fclose(fptr);
    return NULL;
  }

  while(!feof(fptr))
  {
    int _char = fgetc(fptr);
    if(_char != EOF)
    {
      arr[(int)_char] += 1;
      ++(*counter);
    }
  }
  fclose(fptr);
  return arr;
}

int writeCount(char *filename, unsigned long *arr)
{
  FILE *fptr = fopen(filename, "w");
  if(fptr == NULL)
  {
    fclose(fptr);
    return 0;
  }
  int size = 256;//(sizeof(*arr) /  sizeof(arr[0]));
  if(fwrite(arr, sizeof(unsigned long), size, fptr) != size)
  {
    fclose(fptr);
    return 0;
  }
  fclose(fptr);
  return(size);
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------*/
static treeNode* createTNode(char ch1, unsigned long freq1)
{
  treeNode *tn = malloc(sizeof(treeNode));
  tn -> left = NULL;
  tn -> right = NULL;
  tn -> value = ch1;
  tn -> freq = freq1;
  return tn;
}

static listNode *addListNode(treeNode *tNode)
{
  listNode *ln = malloc(sizeof(listNode));
  ln -> next = NULL;
  ln -> treePoint = tNode;
  return ln;
}

listNode* buildLinked(unsigned long *arr, int size)
{
  int index = 0;
  while(arr[index] == 0)
  {
    ++index;
  }

  if(index == size)
  {
    return NULL; //means array has no letters w/ freq > 0
  }
  listNode *head = malloc(sizeof(listNode));
  head -> treePoint = createTNode(index, arr[index]);
  head -> next = NULL;
  listNode *lNode = head;
  ++index;
  while(index < size)
  {
    if(arr[index] > 0)
    {
      treeNode *tnode = createTNode(index, arr[index]);
      lNode -> next  = addListNode(tnode);
      lNode -> next -> next = NULL;
      lNode = lNode -> next;
    } 
    ++index;
  }
  return head;
}

/*\/\/\/\/\/\\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\\.\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
static void writeTreeHelper(treeNode *tn, int *counter, char *arr)
{
  if(tn == NULL)
    return;
  if(tn->value == 0){
      arr[(*counter)] = '0';
      ++(*counter);
  }
  else if(tn->value != 0){
    arr[(*counter)] = '1';
    ++(*counter);
    arr[(*counter)] = (char)(tn -> value);
    ++(*counter);
  }
  writeTreeHelper(tn->left, counter, arr);
  writeTreeHelper(tn->right, counter, arr);
}
writeTree(char *filename, treeNode *tn, int *counter, char *arr)
{
  if(tn == NULL)
    return;
  FILE *fptr = fopen(filename, "w");
  if(fptr == NULL)
  {
    fclose(fptr);
    return;
  }
  writeTreeHelper(tn, counter, arr);
  arr[((*counter) + 1)] = NULL;
  fputs(arr, fptr);
  fclose(fptr);
  return;
}
/*\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\
 */
static int writeCodeHelper(treeNode *tn, int *arr, int *ind)
{
  if(tn == NULL)
    return arr;
  treeNode *left = tn->left;
  treeNode *right = tn->right;
  if(left == NULL && right == NULL){
    arr[(*ind)] = tn->value;
    ++(*ind);
  }
  writeCodeHelper(left, arr, ind);
  writeCodeHelper(right, arr, ind);
}
void writeCode(char *filename, int **codeTable, int row, int col, treeNode *tn, int *arr)
{
  if(*codeTable == NULL)
    return;
  FILE *fptr = fopen(filename, "w");
  if(fptr == NULL)
  {
    fclose(fptr);
    return;
  }
  int arrInd = 0;
  arr = writeCodeHelper(tn, arr, &arrInd);
  for(int i = 0; i < arrInd; i++)
  {
    char character = arr[i];
    fputc(character, fptr);
    fputc(':', fptr);
    for(int j = 0; j < col; j++)
    {
      if(codeTable[((int)character)][j] == 1)
	fputc('1',fptr);
      if(codeTable[((int)character)][j] == 0)
	fputc('0', fptr);
    }
   fprintf(fptr, "\n"); 
  } 
  fclose(fptr);
  return;
}
/*\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\\/\/\/\/\/\/\/\/\/\/\/\*/
static void compressFileHelper(FILE *outputF, unsigned char bit, unsigned char *bitIndex, unsigned char *endOfByte)
{
  if((*bitIndex) == 0)
    (*endOfByte = 0);
  unsigned char temp = bit << (7 - (*bitIndex));
  *(endOfByte) |= temp;
  if((*bitIndex) == 7)
  {
   // printf("%c",(*endOfByte));
    fwrite(endOfByte, sizeof(unsigned char), 1, outputF);
  }
  ++(*bitIndex);
  //(*bitIndex) %= 8;
  if((*bitIndex) == 8)
    (*bitIndex) = 0;
  return;
}
static void numCompressed(treeNode *tn,  int **codeBook, unsigned long *counter)
{
  if(tn == NULL)
    return;
  treeNode *left=tn->left;
  treeNode *right=tn->right;
  if(left == NULL && right == NULL)
  {
    int row = (int)tn->value;
    (*counter) += 1;
    return;
  }
  numCompressed(left, codeBook, counter);
  numCompressed(right, codeBook, counter);
   return;
}
static void preOrderTraversalOutput(FILE *fptr2, treeNode *tn, unsigned char *bitIndex, unsigned char *endOfByte)
{
  if(tn == NULL)
    return;
  treeNode *left = tn->left;
  treeNode *right = tn->right;
  if(left == NULL && right == NULL){
    compressFileHelper(fptr2, 1, bitIndex, endOfByte);
    unsigned char temp = 0x40;
     while(temp > 0)
     {
       compressFileHelper(fptr2, ((tn->value) & temp) == temp, bitIndex, endOfByte);
       temp>>=1;
     }
     return;
   }
   preOrderTraversalOutput(fptr2, left, bitIndex, endOfByte);
   preOrderTraversalOutput(fptr2, right, bitIndex, endOfByte);
}
void compressFile(char *inputFile, char *outputFile, int **codeTable, int rowMax, int colMax, treeNode *tn, unsigned long decompTotal, int sizeA, int sizeB)
{
  FILE *fptr1 = fopen(inputFile, "r");
  if(fptr1 == NULL){
    fclose(fptr1);
    return;
  }
  FILE *fptr2 = fopen(outputFile, "wb");
  if(fptr2 == NULL){
    fclose(fptr2);
    fclose(fptr1);
    return;
  } 
  //1. do summation on front to find total numbers in uncrompressed file
  //3. seek to end and do ftell to return that
  //2. next do preorder traversal to find each bit and character (8 bytes) to print out
  unsigned long compressedCounter = 0;
  unsigned char bitCounter = 0;
  unsigned char byteMax = 0;
  int preorderNum = (sizeA - sizeB);
  printf("preorderNum is: %d\n", preorderNum);
  numCompressed(tn, codeTable, &compressedCounter);
  //compressedCounter *= 8;
  compressedCounter += 24;
  compressedCounter += (preorderNum);
  printf("Compressed Count  is: %d", compressedCounter);
  fwrite(&compressedCounter, sizeof(unsigned long), 1, fptr2);
  preOrderTraversalOutput(fptr2, tn, &bitCounter, &byteMax);
  fwrite(&decompTotal, sizeof(unsigned long), 1, fptr2);
  bitCounter = 0;
  byteMax = 0;
  int row = 0;
  int col = 0;
  while(!feof(fptr1))
  {
    char buffer = fgetc(fptr1);
    if(buffer != EOF)
    {
      row = (int)buffer;
      col = 0;
      while(col < colMax && (codeTable[row][col] != -1))
      {
        unsigned char temp = codeTable[row][col];
        compressFileHelper(fptr2, (codeTable[row][col] == 1), &bitCounter, &byteMax);
        ++col;
      }
    }
  }
  while(byteMax > 0) //this is only needed when the final byte is not completely full
  {
    compressFileHelper(fptr2, 0, &bitCounter, &byteMax);
  }
  fclose(fptr1);
  fclose(fptr2);
  return;
}
      
 













