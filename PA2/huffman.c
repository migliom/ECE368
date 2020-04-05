#include <stdlib.h>
#include <stdio.h>
#include "huffman.h"

static treeNode *mergeHuffTree(treeNode *t1, treeNode *t2)
{
  treeNode *tn = malloc(sizeof(treeNode));
  tn -> left = t1;
  tn -> right = t2;
  tn -> value = 229;
  tn -> freq = ((t1->freq) + (t2->freq));
  return tn;
}

static listNode *addListNode(treeNode *t1)
{
  listNode *ln = malloc(sizeof(listNode));
  ln -> next = NULL;
  ln -> treePoint = t1;
  return ln;
}
static listNode *insertNode(listNode *head, listNode *ln)
{
  if(head == NULL)
    return ln;
  if((ln->treePoint->freq) < (head->treePoint->freq))
  {
    ln -> next = head; //setting ln  to beginning of list if it is the smallest
    return ln; //-->easy return (best case scenario)
  }
  (head->next) = insertNode(head->next, ln);
  return head;
}

listNode *buildHuff(listNode *listN)
{
  while((listN -> next) != NULL)
  {
    listNode *lSecond = listN -> next; //node after head
    listNode *lThird = lSecond -> next; //need third pointer to maintain order and not lose the linked list
    treeNode *t1 = listN -> treePoint; //take tree values
    treeNode *t2 = lSecond -> treePoint; //take tree values
    free(listN); //free the head and next pointers
    free(lSecond);
    listN = lThird;
    treeNode *mergedTree = NULL;
    mergedTree = mergeHuffTree(t1, t2); //malloc for a new tree to be compiled
    listNode *newListNode = addListNode(mergedTree);
    listN = insertNode(listN, newListNode);
  }
  return listN;
}
   
  
  
