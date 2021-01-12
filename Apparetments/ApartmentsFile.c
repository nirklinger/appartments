#include "ApartmentsFile.h"

void writeApartmentsToBinaryFile(ApartmentsList *aptList) 
{
	if (isEmptyList(aptList))
	{
		remove(APARTMENTS_FILE);
		return;
	}
	
	FILE *apartmentsFile = fopen(APARTMENTS_FILE, "wb");
	checkFailedFileOpen(apartmentsFile);	
	
	fseek(apartmentsFile, sizeof(unsigned int), SEEK_SET);

	ApartmentNode *node = aptList->head;
	unsigned int nodeCount = 0;
	
	while (node != NULL)
	{
		writeApartmentToFile(apartmentsFile, node->apartment);
		node = node->next;
		nodeCount++;
	}

	rewind(apartmentsFile);
	fwrite(&nodeCount, sizeof(unsigned int), 1, apartmentsFile);
	fclose(apartmentsFile);
}

void buildCompressedData(BYTE *compressedData, short int roomCount, EntryDate* date)
{
	compressedData[0] = roomCount << 4 | date->day >> 1;
	compressedData[1] = date->day << 7 | date->month<<3 | (date->year<<1)>>5;
	compressedData[2] = date->year << 4;
}

void writeApartmentToFile(FILE* file, Apartment *apt)
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

void loadApartmentsFromFile(ApartmentsList *aptList)
{
	FILE *file = fopen(APARTMENTS_FILE, "rb");

	if (file == NULL)
	{
		return;
	}

	unsigned int aptCount;

	fread(&aptCount, sizeof(unsigned int), 1, file);
	unsigned short int maxApartmentCode = 0;
	for (unsigned int i = 0; i < aptCount; i++)
	{
		Apartment *apt = readApartmentFromFile(file);
		addApartmentSortedByPrice(aptList, apt);

		if ((apt->id) > maxApartmentCode)
			maxApartmentCode = apt->id;
	}
	fclose(file);
	setLastApartmentCode(maxApartmentCode);
}

Apartment* readApartmentFromFile(FILE* file)
{
	BYTE compressedData[3];
	unsigned short int addressLength, id, roomCount, day, month, year;
	char* address;
	int price;
	time_t dbEntryTime;

	fread(&id, SHORT_SIZE, 1, file);
	fread(&addressLength, SHORT_SIZE, 1, file);

	address = (char*)malloc(addressLength + 1);
	checkFailedMalloc(address);
	fread(address, 1, addressLength, file);
	address[addressLength] = '\0';
	
	fread(&price, sizeof(int), 1, file);
	fread(&dbEntryTime, sizeof(time_t), 1, file);
	fread(compressedData, 1, 3, file);

	parseCompressedData(compressedData, &roomCount, &day, &month, &year);
	Apartment *apt = createApartment(id, address, price, roomCount, day, 
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