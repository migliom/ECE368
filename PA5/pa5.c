#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
static long *Load_Into_Array(char *filename, int *size)
{
	FILE *fptr = fopen(filename, "rb");
	if(fptr == NULL)
		return NULL;
	
	fseek(fptr, 0 , SEEK_END);
	(*size) = ftell(fptr);
	(*size) /= (sizeof(long));
	
	if(!(*size))
	{
		fclose(fptr);
		return NULL;
	}
	long *Arr = malloc((*size) * sizeof(long));
	fseek(fptr, 0, SEEK_SET);
	
	int index = 0;
	while(fread(&Arr[index], sizeof(long), 1, fptr))
	{
		//fprintf(stdout, "%ld\n", Arr[index]);
		index++;
	}
	
	fclose(fptr);
	return Arr;
}

static int Save_From_Array(char *filename, long *arr, int size)
{
	FILE *fptr = fopen(filename, "wb");

	if(fptr == NULL)
	{
		return 0;
	}

	if(fwrite(arr, sizeof(long), size, fptr) != size)
	{
		fclose(fptr);
		return 0;
	}
	fclose(fptr);
	return(size);
}
int main(int argc, char ** argv)
{
	if(argc != 4)
		return EXIT_FAILURE;

	int Size = 0;
	long *Array = NULL;

	Array = Load_Into_Array(argv[2], &Size);
	
	if(Size != 0)
	{
		if(argv[1][1] == 'm')
			Merge_Sort(Array, Size);

		if(argv[1][1] == 'q')
			Quick_Sort(Array, (Size));
	}
	printf("----------------------------\n");
	//for(int i = 0; i < Size; i++)
	//	fprintf(stdout, "%ld\n", Array[i]);
	int saved = Save_From_Array(argv[3], Array, Size);
	
	printf("Saved to file: %d", saved); 
	free(Array);
	return EXIT_SUCCESS;
}
