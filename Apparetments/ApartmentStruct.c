#include "ApartmentStruct.h"

BOOL isEmptyList(ApartmentsList *apartments)
{
	return (apartments->head == NULL) ? true : false;
}

void freeApartment(Apartment * apt)
{
	free(apt->entryDate);
	//free(apt->address);
	free(apt);
}

void freeApartmentNode(ApartmentNode *node)
{
	freeApartment(node->apartment);
	free(node);
}

void makeEmptyApartmentsList(ApartmentsList *aptList)
{
	aptList->tail = aptList->head = NULL;
}

ApartmentNode* createApartmentNode(Apartment *apt, ApartmentNode *next)
{
	ApartmentNode *newNode = (ApartmentNode*)malloc(sizeof(ApartmentNode));
	checkFailedMalloc(newNode);
	newNode->apartment = apt;
	newNode->next = next;

	return newNode;
}

EntryDate* createEntryDate(short int day, short int month, short int year)
{
	EntryDate *newDate = (EntryDate*)malloc(sizeof(EntryDate));
	checkFailedMalloc(newDate);
	newDate->day = day;
	newDate->month = month;
	newDate->year = year;

	return newDate;
}

Apartment* createApartment(unsigned short int id, char* address, int price,
	short int roomCount, short int day, short int month, short int year, time_t dbEntryTime)
{
	Apartment *apartment = (Apartment*)malloc(sizeof(Apartment));
	checkFailedMalloc(apartment);
	apartment->id = id;
	apartment->address = address;
	apartment->price = price;
	apartment->roomCount = roomCount;
	apartment->entryDate = createEntryDate(day, month, year);
	apartment->dbEntryTime = dbEntryTime;

	return apartment;
}

Apartment* createApartmentWithNowTimestamp(unsigned short int id, char* address, int price,
	short int roomCount, short int day, short int month, short int year)
{
	time_t nowTime = time(NULL);
	Apartment *apt = createApartment(id, address, price, roomCount, day, month, year, nowTime);

	return apt;
}
