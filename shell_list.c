#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shell_list.h"
typedef struct _col{
  Node *node;
  struct _col *next;
}Column;

static void *addNode(Node *add, long varo)
{

   if(add -> next == NULL)
   {
     add -> next  = malloc(sizeof(Node));
     add -> next -> value = varo; 
     add -> next -> next = NULL;
     return;
    }
}
Node *List_Load_From_File(char *filename)
{
  FILE *fptr = fopen(filename, "rb");
  if(fptr == NULL)
  {
    fclose(fptr);
    return NULL;
  }
  int seek = fseek(fptr, 0, SEEK_END);
  if(seek != 0)
  {
    fclose(fptr);
    return NULL;
  }
  fseek(fptr, 0, SEEK_SET);

  long temp_value;
  Node *head = NULL;
  head = malloc(sizeof(Node));
  Node *q = head; 
  q -> next = NULL;
  int firstTime = 0;
  while(fread(&temp_value, sizeof(long), 1, fptr))
  {
    if(firstTime != 1)
    {
      q -> value = temp_value;
      ++firstTime;
    }
    else
    {
      addNode(q, temp_value);
      q = q -> next;
    }
  }
  fclose(fptr);
  return head;
} 

//------------------------------------------------------------------------//
//------------------------------------------------------------------------//

static Column *deleteColumns(Column *colHead)
{
  Column *q = colHead;
  while(q != NULL)
  {
    Column *temp = q -> next;
    free(q);
    q = temp;
  }
  return q;
}
static Column *buildColumns(Column *head, int k)
{
  Column *q = head;
  q -> next = NULL;
  for(int i = 0; i < (k-1); i++)
  {
    q -> next = malloc(sizeof(Column));
    q = q -> next;
    q -> next = NULL;
  }

  return head;
}
//--------------------------------------------------------------------------//
static Column *addNodes(Column *head, Node *List, int k, int size)
{
  int totalCount = 1;
  Column *cq = head;
  int tracker = 0; //ind to compare with k
  Node *p = List; //resetter for list
  Node *q = List; //node to traverse while list
  Node *n, *temp; //temp variable to maintain addresses
  p = p->next;
  cq->node = n;
  n = q;
  q = q->next;
  ++tracker;
  n -> next = NULL;
  temp = q;
  ++totalCount; 
  while(totalCount < size)
  {
    cq -> node = n;
    while(q != NULL)
    {
      if(tracker = k)
      {
        q = q->next;
        tracker = 0;
        temp->next = q->next;
        temp = q;  
        q = q->next;
        n = temp;
        temp = q;
        n->next = NULL;
        ++tracker;
      }
      
      ++tracker;
        
    }
    q = p; 
  }
}
//-------------------------------------------------------------------------//

static Node *swap(Node *ptr1, Node *ptr2)
{
  Node *temp = ptr2->next;
  ptr2->next = ptr1;
  ptr1->next = temp;
  return ptr2;
}
static Column *sortCol(Column *head, int k, int size)
{
  Column *colTracker = head;
  int i, j, on, depth = 0; //integers to keep track of for loop
  while(colTracker != NULL)
  {
    Node *h = colTracker -> node;
    Node *depthCounter = h;
    while(depthCounter != NULL)
    {
      depthCounter = depthCounter -> next;
      ++depth;
    }
    if(depth > 1)
    {
      for(i = 0; i < depth; i++)
      {
        h = colTracker -> node;
        on = 0; //to know when to swap values
        for(j = 0; j < depth - i - 1; j++)
        {
          Node *p1 = h;
          Node *p2 = p1 -> next;
          if(p1->value > p2->value)
          {
            h = swap(p1, p2);
            colTracker -> node = h;
            on = 1;
          }
          h = h->next;
        }
        if(on == 0)
          break;
      }
    }
    colTracker = colTracker -> next;
    depth = 0;
  }
  return head;
}
//--------------------------------------------------------------------------//
static Node *putBack(Column *head, Node *list, int k, int size)
{
  //RECOMBINING LINKED LIST
  //CANT FIGURE OUT HOW TO RETURN WHOLE LINKEDLIST -> LIST WONT UPDATE 
  //LIST STAYS THE FIRST NODE IN THE COLUMN INSTEAD OF UPDATING
  Node *listPut;
  int kcount = 1;
  int kDepth = 0;
  int i = 1;
  Column *colHelper = head;
  Column *colHelper2 = colHelper;
  Node *q;
  listPut = colHelper2 -> node;
  list = listPut;
  colHelper2->node = colHelper2->node->next;
  colHelper2 = colHelper2 -> next;
  while(kcount != size)
  {
    while(colHelper2 != NULL)
    {
      q = colHelper2->node;
      if(colHelper2->node->next != NULL)
        colHelper2 -> node = colHelper2->node->next;
      listPut -> next = q;  
      listPut = listPut->next;
      ++kcount;
      if(kcount == size)
        break;
      colHelper2 = colHelper2->next;
    }
    colHelper2 = colHelper;
  }
  //listPut = NULL;
  return list;
}
//--------------------------------------------------------------------------//
Node *List_Shellsort(Node *List, long *n_comp)
{
  int size = 0;
  Node *q = List;
  while(q != NULL)
  {
    ++size;
    q = q->next;
  }
  Column *head = NULL;
  head = malloc(sizeof(Column));
 
  int k = 0;
  while(k < size)
  {
    k = (k*3) + 1;
  }
  k = (k-1) / 3;
  head = buildColumns(head, k); 
  while(k > 0)
  {
    //head = addNodes(head, List, k, size);
    //head = sortCol(head, k, size);
    //List = putBack(head, List, k, size);
    head = deleteColumns(head);
    head = malloc(sizeof(Column));
    if((k/3) > 0)
      head = buildColumns(head, (k/3));
    k = (k-1) / 3;
  }
  n_comp = 0;
  free(head);
  return(List);
}
//-------------------------------------------------------------------------//
//-------------------------------------------------------------------------//
int List_Save_To_File(char *filename, Node *List)
{
  int numSaves;
  FILE *fptr = fopen(filename, "wb");
  if(fptr == NULL)
  {
    fclose(fptr);
    return(0);
  }
  Node *listP = List;
  while(listP != NULL)
  {
    fwrite(listP, sizeof(listP), 1, fptr);
    ++numSaves;
    listP = listP->next;
  }
  fclose(fptr);
  return(numSaves);
}
