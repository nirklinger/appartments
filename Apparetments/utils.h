#ifndef UTILS
#define UTILS
#include <stdlib.h>
#include <stdio.h>
#define true 1
#define false 0
typedef int BOOL;

void checkFailedMalloc(void* pointer);

void checkFailedFileOpen(FILE* file);
#endif