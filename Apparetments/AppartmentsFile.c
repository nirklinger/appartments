#include "AppartmentsFile.h"

int writeAppartmentsToBinaryFile(AppartmentsList *aptList) 
{
	if(isEmptyList(aptList))
	{
		return;
	}

	FILE *appartmentsFile = fopen(APPARTMENTS_FILE, "wb");

	AppartmentNode *node = aptList->head;

	while (node != NULL)
	{
		writeAppartmentToFile(appartmentsFile, node->appartment);
		node = node->next;
	}

	fclose(appartmentsFile);
}

void buildCompressedData(BYTE *compressedData, short int roomCount, EntryDate* date)
{
	compressedData[0] = roomCount << 4 | date->day >> 1;
	compressedData[1] = date->day << 7 | date->month<<3 | (date->year<<1)>>5;
	compressedData[2] = date->year << 4;
}

void writeAppartmentToFile(FILE* file, Appartment *apt)
{
	BYTE compressedData[3];
	buildCompressedData(compressedData, apt->roomCount, apt->entryDate);
	unsigned short int addressLength = strlen(apt->address);
	
	fwrite(&(apt->id), SHORT_SIZE, 1, file);
	fwrite(&addressLength, SHORT_SIZE, 1, file);
	fwrite(apt->address, 1, addressLength, file);
	fwrite(&(apt->price), sizeof(int), 1, file);
	fwrite(&(apt->dbEntryTime), sizeof(time_t), 1, file);
	fwrite(compressedData, 1, 3, file);
}