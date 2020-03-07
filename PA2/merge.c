#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "huffman.h"
static void splitHalf(listNode *top, listNode **front, listNode **back)
{
  listNode *fast, *slow;
  slow = top;
  fast = top -> next;

  while(fast != NULL)
  {
    fast = fast -> next;
    if(fast != NULL)
    {
      slow = slow -> next;  //moves one space to get to halfway
      fast = fast -> next; //fast moves two spaces for every one space of slow
    }
  }
  //slow becomes the midpoint of the list 
  *front = top;
  *back = slow -> next;
  slow -> next = NULL;
}
static listNode* sortMerge(listNode *node1, listNode *node2)
{
  listNode *final = NULL;
  if(node1 == NULL){
    return node2;
  }
  else if(node2 == NULL){
    return(node1);
  }
  if((node1 -> treePoint -> freq) <= (node2 -> treePoint -> freq))
  {
    final = node1;
    final -> next = sortMerge(node1->next, node2);
  }

  else
  {
    final = node2;
    final -> next = sortMerge(node1, node2->next);
  }
  return final;
}
void mergeSort(listNode ** head)
{
  listNode *headTemp = *head;
  if((headTemp == NULL) || (headTemp -> next == NULL))
  {
    return; //list has zero or one element (no sorting needed)
  }

  listNode *node1, *node2;
  splitHalf(headTemp, &node1, &node2); //splits the list in half sublists
  mergeSort(&node1); //recursion so repeat process
  mergeSort(&node2);  //recursion
  *head = sortMerge(node1, node2); //merge the two sorted sublists
}
  
