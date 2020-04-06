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
Node *List_Load_From_File(char *filename, int *totCount)
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
	(*totCount) = 1;
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
			++(*totCount);
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
		q -> next -> node = NULL;
    q = q -> next;
    q -> next = NULL;
  }
	//q -> next = head;
  return head;
}
//--------------------------------------------------------------------------//
static Node *pq_sort(Node **head, Node *nodeMover, long *n_comp)
{
	Node * temp = NULL;
	Node * curr = (*head) -> next;
	Node * prev = (*head);

	while(curr != NULL && (curr -> value) < (nodeMover -> value))
	{
		++(*n_comp);
		curr = curr->next;
		prev = prev -> next;
	}

	prev -> next = nodeMover;
	temp = nodeMover -> next;
	prev -> next -> next = curr;
	return temp;
}

static Column *addNodes(Column *head, Node *List, int k, int size, long *n_comp)
{
	Column *colMover = head -> next;
	Node * nodeMover = List -> next;

	head -> node = List;
	head -> node -> next = NULL;
	Node *temp = NULL;
	Node *colNodeTemp = NULL;
	while(nodeMover != NULL)
	{
		if(colMover == NULL)
			colMover = head;
		Node * colNode = colMover -> node;
		if(colNode == NULL){
			++(*n_comp);
			temp = nodeMover -> next;
			colNode = nodeMover;
			colNode -> next = NULL;
			nodeMover = temp;
			colMover -> node = colNode;
			colMover = colMover -> next;
		}
		else{
			if(nodeMover -> value <= colNode -> value)
			{
				++(*n_comp);
				colNodeTemp = colNode;
				colMover -> node = nodeMover;
				temp = nodeMover -> next;
				colMover -> node -> next = NULL;
				colMover -> node -> next = colNodeTemp;
				nodeMover = temp;
			}
			else
				nodeMover = pq_sort(&(colMover->node), nodeMover, n_comp);
			colMover = colMover -> next;
		}
	}	
	return head;
}
//------------------------------------------------------------------------
//--------------------------------------------------------------------------//
static Node *putBack(Column *head, Node *list, int k, int size)
{
  //RECOMBINING LINKED LIST
  //CANT FIGURE OUT HOW TO RETURN WHOLE LINKEDLIST -> LIST WONT UPDATE 
  //LIST STAYS THE FIRST NODE IN THE COLUMN INSTEAD OF UPDATING
	Column *colMover = head -> next;
	Node *temp = NULL;
	int counter = 0;
	
	list = head -> node;
	Node *listMover = list;
	temp = head -> node -> next;
	listMover -> next = NULL;
	head -> node = temp;

	while(((++counter) % size) != 0)
	{
		if(colMover == NULL)
			colMover = head;
		temp = colMover -> node -> next;
		listMover -> next = colMover -> node;
		(listMover -> next -> next) = NULL;
		listMover = listMover -> next;
		colMover -> node = temp;
		colMover = colMover -> next;
	}
  return list;
}
//--------------------------------------------------------------------------//
Node *List_Shellsort(Node *List, long *n_comp, int totalNums)
{
  int size = 0;
  Column *head = NULL;
  head = malloc(sizeof(Column));
 	Node *q = NULL;
  int k = 0;
  while(k < totalNums)
  {
    k = (k*3) + 1;
  }
  k = (k-1) / 3;
  head = buildColumns(head, k); 
  while(k > 0)
  {
    head = addNodes(head, List, k, totalNums, n_comp);
    List = putBack(head, List, k, totalNums);
    head = deleteColumns(head);
    head = malloc(sizeof(Column));
    if((k/3) > 0)
      head = buildColumns(head, (k/3));
    k = (k-1) / 3;
  }
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
