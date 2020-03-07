#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shell_array.h"
#include "shell_list.h"

int main(int argc, char * * argv)
{
  if(argc != 4)
  {
    //fprint(stderr, "need a valid input\n");
    return EXIT_FAILURE;
  }
  int numbers_saved = 0;
  int size;
  long n_comp = 0;
  if((argv[1][1]) == 'a')
  {
     long *arr =  Array_Load_From_File(argv[2], &size);
     if(arr == NULL)
       return EXIT_FAILURE;
     Array_Shellsort(arr, size, &n_comp);
     numbers_saved = Array_Save_To_File(argv[3], arr, size);
     printf("Number of comparisons: %ld\n\n", n_comp);
     free(arr);
     return EXIT_SUCCESS;
  }

  if((argv[1][1]) == 'l')
  {
    Node *head = NULL;
    head = List_Load_From_File(argv[2]);
    Node *p = head;
    head = List_Shellsort(head, &n_comp);
    numbers_saved = List_Save_To_File(argv[3], head); 
    //printf("Numbers saved to file: %d\nNumber of comparisons: %ld\n\n", numbers_saved, n_comp);
   printf("Number of Comparisons: %ld\n", n_comp);
   while(p!=NULL)
   {
     Node *temp = p->next;
     free(p);
     p = temp;
   }
    return EXIT_SUCCESS;  
  }
}
