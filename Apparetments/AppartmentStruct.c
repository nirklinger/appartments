#include <time.h>
#include <stdlib.h>
#include "AppartmentStruct.h"
#include <stdbool.h>

bool isEmptyList(AppartmentsList *appartments)
{
	return (appartments->head == NULL) ? true : false;
}

void freeAppartment(Appartment * apt)
{
	free(apt->entryDate);
	free(apt);
}

void freeAppartmentNode(AppartmentNode *node)
{
	freeAppartment(node->appartment);
	free(node);
}

void makeEmptyAppartmentsList(AppartmentsList *aptList)
{
	aptList->tail = aptList->head = NULL;
}

AppartmentNode* createAppartmentNode(Appartment *apt, AppartmentNode *next)
{
	AppartmentNode *newNode = (AppartmentNode*)malloc(sizeof(AppartmentNode));
	newNode->appartment = apt;
	newNode->next = next;

	return newNode;
}

EntryDate* createEntryDate(short int day, short int month, short int year)
{
	EntryDate *newDate = (EntryDate*)malloc(sizeof(EntryDate));
	newDate->day = day;
	newDate->month = month;
	newDate->year = year;

	return newDate;
}

Appartment* createAppartment(unsigned int id, char* address, int price,
	short int roomCount, short int day, short int month, short int year, time_t dbEntryTime)
{
	Appartment *appartment = (Appartment*)malloc(sizeof(Appartment));
	appartment->id = id;
	appartment->address = address;
	appartment->price = price;
	appartment->roomCount = roomCount;
	appartment->entryDate = createEntryDate(day, month, year);
	appartment->dbEntryTime = dbEntryTime;

	return appartment;
}

Appartment* createAppartmentWithNowTimestamp(unsigned int id, char* address, int price,
	short int roomCount, short int day, short int month, short int year)
{
	time_t nowTime;
	nowTime = time(NULL);
	Appartment *apt = createAppartment(id, address, price, roomCount, day, month, year, nowTime);

	return apt;
}
