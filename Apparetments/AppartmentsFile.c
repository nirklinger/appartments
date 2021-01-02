#include "AppartmentsFile.h"

int writeAppartmentsToBinaryFile(AppartmentsList *aptList) 
{
	if(isEmptyList(aptList))
	{
		return;
	}

	FILE *appartmentsFile = fopen(APPARTMENTS_FILE, "wb");
	fseek(appartmentsFile, sizeof(unsigned int), SEEK_SET);

	AppartmentNode *node = aptList->head;
	unsigned int nodeCount = 0;
	
	while (node != NULL)
	{
		writeAppartmentToFile(appartmentsFile, node->appartment);
		node = node->next;
		nodeCount++;
	}

	rewind(appartmentsFile);
	fwrite(&nodeCount, sizeof(unsigned int), 1, appartmentsFile);
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

void loadAppartmentsFromFile(AppartmentsList *aptList)
{
	FILE *file = fopen(APPARTMENTS_FILE, "rb");

	if (file == NULL)
	{
		return;
	}

	unsigned int aptCount;

	fread(&aptCount, sizeof(unsigned int), 1, file);
	unsigned short int maxAppartmentCode = 0;
	for (unsigned int i = 0; i < aptCount; i++)
	{
		Appartment *apt = readAppartmentFromFile(file);
		addAppartmentSortedByPrice(aptList, apt);

		if ((apt->id) > maxAppartmentCode)
			maxAppartmentCode = apt->id;
	}
	fclose(file);
	setLastAppartmentCode(maxAppartmentCode);
}

Appartment* readAppartmentFromFile(FILE* file)
{
	BYTE compressedData[3];
	unsigned short int addressLength, id, roomCount, day, month, year;
	char* address;
	int price;
	time_t dbEntryTime;

	fread(&id, SHORT_SIZE, 1, file);
	fread(&addressLength, SHORT_SIZE, 1, file);

	address = (char*)malloc(addressLength + 1);
	fread(address, 1, addressLength, file);
	address[addressLength] = '\0';
	
	fread(&price, sizeof(int), 1, file);
	fread(&dbEntryTime, sizeof(time_t), 1, file);
	fread(compressedData, 1, 3, file);

	parseCompressedData(compressedData, &roomCount, &day, &month, &year);
	Appartment *apt = createAppartment(id, address, price, roomCount, day, 
		month, year, dbEntryTime);

	return apt;
}

void parseCompressedData(BYTE* compressedData, 
	unsigned short int* roomCount, 
	unsigned short int* day, 
	unsigned short int* month, 
	unsigned short int* year)
{
	*roomCount = compressedData[0] >> 4;
	*day = (compressedData[0] & 15) << 1 | compressedData[1] >> 7;
	*month = (compressedData[1] & 120) >> 3;
	*year = (compressedData[1] & 7) << 4 | (compressedData[2] & (~15)) >> 4;
}