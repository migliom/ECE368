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

  if(index == (size + 1))
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
static int writeTreeHelper(treeNode *tn, FILE *fptr1)
{
  if(tn == NULL)
    return;
	
	if(tn -> left == NULL) //&& tn->value != 1)
	{
		fputc('1', fptr1);
		int temp = tn -> value;
		fputc(temp, fptr1);}

  if((tn->left != NULL) && (tn->right != NULL)){
			fputc('0', fptr1); 
  }
	/*else if((tn -> value) == 1)
		return 1;
  else if(tn->value != 229){
		fputc('1', fptr1);
		int temp = tn -> value;
		fputc(temp, fptr1);
  }*/
  writeTreeHelper(tn->left, fptr1);
  writeTreeHelper(tn->right, fptr1);
	return 0;
}
writeTree(char *filename, treeNode *tn)
{
  FILE *fptr = fopen(filename, "w");
  if(fptr == NULL)
  {
    return;
  }
  int emptyCheck = writeTreeHelper(tn, fptr);
  fclose(fptr);
  return emptyCheck;
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
	if(arrInd > 1){
  	for(int i = 0; i < arrInd; i++)
  	{
    	fputc(arr[i], fptr);
    	fputc(':', fptr);
    	for(int j = 0; j < col; j++)
    	{
      	if(codeTable[(arr[i])][j] == 1)
					fputc('1',fptr);
      	if(codeTable[(arr[i])][j] == 0)
					fputc('0', fptr);
    	}
   	fprintf(fptr, "\n"); 
		}
  } 
  fclose(fptr);
  return;
}
/*\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\\/\/\/\/\/\/\/\/\/\/\/\*/
static void compressFileHelper(FILE *outputF, unsigned char bit, unsigned char *bitIndex, unsigned char *endOfByte)
{
  unsigned char temp = bit << (*bitIndex);
  *(endOfByte) |= temp;
  ++(*bitIndex);

  if((*bitIndex) == 8)
  {
    fwrite(endOfByte, sizeof(unsigned char), 1, outputF);
  	(*bitIndex) = 0;
		(*endOfByte) = 0;
	}

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
    //int row = (int)tn->value;
    (*counter) += 9;
    return;
  }
  numCompressed(left, codeBook, counter);
	if(tn -> value != 1)
		(*counter) += 1;
  numCompressed(right, codeBook, counter);
   return;
}
static void preOrderTraversalOutput(FILE *fptr2, treeNode *tn, unsigned char *bitIndex, unsigned char *endOfByte)
{
  if(tn == NULL)
    return;
  treeNode *left = tn->left;
  treeNode *right = tn->right;
	if(tn->left != NULL){
     compressFileHelper(fptr2, 0, bitIndex, endOfByte); 
  }
  if(left == NULL && right == NULL)
	{
    compressFileHelper(fptr2, 1, bitIndex, endOfByte);
		unsigned char mask = 0x1; //starts at least significant position of 00000001 and goes left
		for(int i = 1; i < 9; i++)
		{
			 compressFileHelper(fptr2, ((tn->value) & mask) == mask, bitIndex, endOfByte);
       mask<<=1; //multiplies by a factor of 2 each time, therefore moving one spot to the left
		}
     return;
   }
   preOrderTraversalOutput(fptr2, left, bitIndex, endOfByte);
   preOrderTraversalOutput(fptr2, right, bitIndex, endOfByte);
}
void compressFile(char *inputFile, char *outputFile, int **codeTable, treeNode *tn, unsigned long decompTotal)
{
  FILE *fptr1 = fopen(inputFile, "r");
  if(fptr1 == NULL){
    return;
  }
  FILE *fptr2 = fopen(outputFile, "wb");
  if(fptr2 == NULL){
    fclose(fptr1);
    return;
  } 
  //1. do summation on front to find total numbers in uncrompressed file
  //3. seek to end and do ftell to return that
  //2. next do preorder traversal to find each bit and character (8 bits) to print out
  unsigned long compressedCounter = 0;
  unsigned char bitCounter = 0;
  unsigned char byteMax = 0;
  
	numCompressed(tn, codeTable, &compressedCounter);

	if(compressedCounter % 8 == 0)
		compressedCounter /= 8;
	else
		compressedCounter = (compressedCounter / 8) + 1;

	unsigned long totalComp = 0;
	fwrite(&totalComp, sizeof(unsigned long), 1, fptr2);

  fwrite(&compressedCounter, sizeof(unsigned long), 1, fptr2);
  fwrite(&decompTotal, sizeof(unsigned long), 1, fptr2);
  preOrderTraversalOutput(fptr2, tn, &bitCounter, &byteMax);
	if(bitCounter > 0)
		fwrite(&byteMax, sizeof(unsigned char), 1, fptr2);
  bitCounter = 0;
  byteMax = 0;
  int row = 0;
  int col = 0;
  while(!feof(fptr1))
  {
    int buffer = fgetc(fptr1);
    if(buffer != EOF)
    {
      row = buffer;
      col = 0;
      while(codeTable[row][col] != -1)
      {
        unsigned char temp = codeTable[row][col];
        compressFileHelper(fptr2, (codeTable[row][col] == 1), &bitCounter, &byteMax);
        ++col;
      }
    }
  }
  if(bitCounter > 0)
		fwrite(&byteMax, sizeof(unsigned char), 1, fptr2);
	
	bitCounter = 0;
  byteMax = 0;
 	 
		totalComp = ftell(fptr2);
	
		int seek = fseek(fptr2, 0, SEEK_SET);

  	fwrite(&totalComp, sizeof(unsigned long), 1, fptr2);
	fclose(fptr1);
  fclose(fptr2);
  return;
}
      
 













