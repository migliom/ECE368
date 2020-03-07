#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shell_array.h"
long *Array_Load_From_File(char *filename, int *size)
{
    long *arr;
    FILE *fptr = fopen(filename, "rb");
    if(fptr == NULL)
    {
        fclose(fptr);
        arr = NULL;
        return 0;
      }
      int contents = fseek(fptr, 0, SEEK_END);

      if(contents != 0)
      {
        fclose(fptr);
        return NULL;
      }
      int temp_size = ftell(fptr);

      contents = fseek(fptr, 0, SEEK_SET);
      if(contents != 0)
      {
        fclose(fptr);
        return NULL;
      }

      *size = (temp_size / sizeof(long));
      arr = malloc((*size) * sizeof(long));
      int index = 0;

      while(fread(&arr[index], sizeof(long), 1, fptr))
      {
        ++index;
      }
    fclose(fptr);
    return arr;
}
void Array_Shellsort(long *array, int size, long *n_comp)
{   
    int ktemp = 0;
    long movingVaro;
    int i = 0;
    while(ktemp <= (size / 3))
    {
      ktemp = (ktemp * 3) + 1; 
    }

    for(int k = ktemp; k > 0; k = ((k - 1) / 3))
    {
      for(int j = k; j < (size); j++)
      {
        movingVaro = array[j];
        i = j;
        while(i >= k && array[i-k] > movingVaro)
        {
          array[i] = array[i-k];
          ++(*n_comp);
          i -= k;
        }
        array[i] = movingVaro;
      }
    } 
}
int Array_Save_To_File(char *filename, long *array, int size)
{
    FILE *fptr = fopen(filename, "wb");

    if(fptr == NULL)
    {
      fclose(fptr);
      return(0);
    }
    if(fwrite(array, sizeof(long), size, fptr) != size)
    {
      fclose(fptr);
      return(0);
    }
    fclose(fptr);
    return(size);
}
