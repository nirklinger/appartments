#ifndef APT_FILE
#define APT_FILE
#define _CRT_SECURE_NO_WARNINGS
#define APPARTMENTS_FILE "./appartments.dat"
#define SHORT_SIZE sizeof(unsigned short int)
#include <stdio.h>
#include <string.h>
#include "AppartmentStruct.h"
#include "AppartmentsCommands.h"

typedef unsigned char BYTE;

int writeAppartmentsToBinaryFile(AppartmentsList *aptList);

void buildCompressedData(BYTE *compressedData, short int roomCount, EntryDate* date);

void writeAppartmentToFile(FILE* file, Appartment *apt);

void loadAppartmentsFromFile(AppartmentsList *aptList);

Appartment* readAppartmentFromFile(FILE* file);

void parseCompressedData(BYTE* compressedData,
	unsigned short int* roomCount,
	unsigned short int* day,
	unsigned short int* month,
	unsigned short int* year);

#endif
