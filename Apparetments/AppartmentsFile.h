#ifndef APT_FILE
#define APT_FILE
#define _CRT_SECURE_NO_WARNINGS
#define APPARTMENTS_FILE "./appartments.dat"
#define SHORT_SIZE sizeof(unsigned short int)
#include <stdio.h>
#include <string.h>
#include "AppartmentStruct.h"

typedef unsigned char BYTE;

int writeAppartmentsToBinaryFile(AppartmentsList *aptList);

void buildCompressedData(BYTE *compressedData, short int roomCount, EntryDate* date);

void writeAppartmentToFile(FILE* file, Appartment *apt);

#endif
