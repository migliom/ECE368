#include <stdlib.h> 
#include <stdio.h>
#include <math.h>
#include "huffman.h"
int max(int one, int two)
{
  if(one >= two)
    return one;
  else
    return two;
}
static int findTreeHeight(treeNode *tNode)
{
  if(tNode == NULL)
    return -1;
  int leftHeight = findTreeHeight(tNode -> left);
  int rightHeight = findTreeHeight(tNode -> right);
  return max(leftHeight, rightHeight) + 1;
}
static int** buildTable(int **table, treeNode *tn, int *tempArr, int *ind)
{
  if(tn == NULL)
  {
    (*ind)--;
    return table;
  }
  treeNode *left = tn -> left;
  treeNode *right = tn -> right;
  if((left == NULL) && (right == NULL))
  {
    int col = 0;
    int row = (tn -> value);
    int tempIndex = 0;
    while(tempIndex <= (*ind))
    {
      table[row][col] = tempArr[tempIndex];
      ++col;
      ++tempIndex;
    }
    --(*ind);
    return table;
  }
  
  if(left != NULL)
  { 
    ++(*ind);
    tempArr[(*ind)] = 0;
    buildTable(table, left, tempArr, ind);
  }
  if(right != NULL)
  {
     ++(*ind);
    tempArr[(*ind)] = 1;
    buildTable(table, right, tempArr, ind);
  }
  --(*ind);
  return table;
}
static void deleteTreeNode(treeNode *root)
{
  if(root == NULL)
    return;
  deleteTreeNode(root->left);
  deleteTreeNode(root->right);
  free(root);
}
void destroy(treeNode *root)
{
  if(root == NULL)
    return;
  deleteTreeNode(root);
  return;
}
int **codeBook(listNode *ln, int *numRows, int *numCols)
{
  (*numCols) = findTreeHeight(ln->treePoint) + 1; //professor Koh special
  int numLeafs = 0; //to be incremented for # of leaves
  numLeafs = 256;
  int **huffArray; // = malloc(numLeafs * sizeof(int*));
  huffArray = (int**)malloc(numLeafs * sizeof(int*));
  int index = 0;
  for(int row = 0; row < (numLeafs); row++)
  {
    (huffArray)[row] = (int*)malloc((*numCols) * sizeof(int)); //dynamically allocate
    while(index < ((*numCols)))
    {
      huffArray[row][index] = -1;
      ++index;
    }
    index = 0;
  }
  treeNode *root = ln->treePoint; //straight tree root now
  //free(ln); //do not need the linked list anymore can just use tree
  int rowTracker = 0; //used for recursive call to increment row in array
  int colTracker = 1; //column start at 1 because first col is the char
  index = 0;
  int tableIndex = -1;
  int *tableArr = (int)malloc((*numCols) * sizeof(int));
  huffArray = buildTable(huffArray, root, tableArr, &tableIndex); //call builder
  free(tableArr);
  return huffArray;
}
