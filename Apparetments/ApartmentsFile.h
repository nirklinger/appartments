#ifndef APT_FILE
#define APT_FILE
#define _CRT_SECURE_NO_WARNINGS
#define ApartmentS_FILE "./apartments.dat"
#define SHORT_SIZE sizeof(unsigned short int)
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "ApartmentStruct.h"
#include "ApartmentsCommands.h"

typedef unsigned char BYTE;

int writeApartmentsToBinaryFile(ApartmentsList *aptList);

void buildCompressedData(BYTE *compressedData, short int roomCount, EntryDate* date);

void writeApartmentToFile(FILE* file, Apartment *apt);

void loadApartmentsFromFile(ApartmentsList *aptList);

Apartment* readApartmentFromFile(FILE* file);

void parseCompressedData(BYTE* compressedData,
	unsigned short int* roomCount,
	unsigned short int* day,
	unsigned short int* month,
	unsigned short int* year);

#endif
