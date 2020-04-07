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
  for(int i = 1; i < (k); i++)
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
static Node *enqueue(Node ** head, Node *insertNode, long *n_comp, int A_D_CHECK)
{
	Node *temp = insertNode -> next;
	insertNode -> next = NULL;
	Node dummy_head;
	dummy_head.next = (*head);
	Node *curr = dummy_head.next;
	Node *prev = &dummy_head;
	if(A_D_CHECK == 1){
		while(curr && curr->value < insertNode -> value)
		{
			++(*n_comp);
			prev = curr;
			curr = curr->next;
		}
	}
	else{
		while(curr && curr->value > insertNode -> value)
		{
			++(*n_comp);
			prev = curr;
			curr = curr->next;
		}
	}
		prev->next = insertNode;
		insertNode -> next = curr;
		(*head) = dummy_head.next;
		return temp;
}
static Column *addNodes(Column *head, Node *List, long *n_comp, int check)
{
	Column *colMover = head -> next;
	Node * nodeMover = List -> next;

	head -> node = List;
	head -> node -> next = NULL;
	Node *temp = NULL;

	while(nodeMover != NULL)
	{
		if(colMover == NULL)
			colMover = head;
		//temp = nodeMover -> next;
		//nodeMover -> next = NULL;
		nodeMover = enqueue(&(colMover -> node), nodeMover, n_comp, check);
		//nodeMover = temp;
		colMover = colMover -> next;
	}	
	return head;
}
//------------------------------------------------------------------------
//--------------------------------------------------------------------------//

static Node *push(Node *head, Node *insert)
{
	insert -> next = head;
	return insert;
}
static Node *putBack(Column *head, Node *list, int k, int size)
{
  //RECOMBINING LINKED LIST
  //CANT FIGURE OUT HOW TO RETURN WHOLE LINKEDLIST -> LIST WONT UPDATE 
  //LIST STAYS THE FIRST NODE IN THE COLUMN INSTEAD OF UPDATING
	int counter = 0;

	Column *colMover = head;
	Node *temp = NULL;

	while(((++counter) % (size + 1)) != 0)
	{
		if(colMover == NULL)
			colMover = head;
		temp = colMover -> node -> next;
		colMover -> node -> next = NULL;
		list = push(list, colMover -> node);
		colMover -> node = temp;
		colMover = colMover->next;
	}
	return list;

	/*Column *colMover = head->next;
	Node *temp = NULL;
	int counter = 0;

	list = head -> node;
	Node *listMover = list;
	temp = head->node->next;
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

	return list;*/
}
//--------------------------------------------------------------------------//
static void reverseHelper(Node *curr, Node *prev, Node **head)
{
	if(!curr->next){
		*head = curr;
		curr->next=prev;
		return;
	}

	Node *next = curr->next;
	curr->next = prev;
	reverseHelper(next, curr, head);
}

void reverse(Node ** head)
{
	if(head == NULL)
		return;
	reverseHelper(*head, NULL, head);
}

Node *List_Shellsort(Node *List, long *n_comp, int totalNums)
{
  Column *head = NULL;
  head = malloc(sizeof(Column));
	head -> next = NULL;
	head -> node = NULL;
 	Node *q = NULL;
  int k = 0;
  while(k < totalNums)
  {
    k = (k*3) + 1;
  }
	int A_D_CHECK = 1;
  k = (k-1) / 3;
  head = buildColumns(head, k); 
	if(k % 2 != 0)
		A_D_CHECK = 0;
  while(k > 0)
  {
    head = addNodes(head, List, n_comp, A_D_CHECK);
		List = NULL;
    List = putBack(head, (List), k, totalNums);
		//reverse(&List, totalNums);
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
	if(listP -> value > listP -> next -> value)
		reverse(&listP);
	int counter = 1;
  while(listP != NULL)
  {
    fwrite(listP, sizeof(listP), 1, fptr);
    ++numSaves;
    listP = listP->next;
  }
  fclose(fptr);
  return(numSaves);
}
