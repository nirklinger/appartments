#include "utils.h"

void checkFailedMalloc(void* pointer)
{
	if (pointer == NULL)
	{
		printf("Fail in memory allocation\n");
		exit(1);
	}
}

void checkFailedFileOpen(FILE* file)
{
	if (file == NULL)
	{
		printf("Fail at open file\n");
		exit(1);
	}
}