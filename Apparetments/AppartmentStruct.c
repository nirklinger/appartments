#include <time.h>
#include <stdlib.h>

typedef struct entryDate {
	short int day;
	short int month;
	short int year;
} EntryDate;

typedef struct appartment {
	unsigned int id;
	char* address;
	int price;
	short int roomCount;
	EntryDate *entryDate;
	time_t dbEntryTime;
} Appartment;

typedef struct appartmentNode {
	struct appartmentNode *next;
	Appartment *appartment;
} AppartmentNode;

typedef struct appartmentsList {
	AppartmentNode *head;
	AppartmentNode *tail;
} AppartmentsList;

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

EntryDate* CreateEntryDate(short int day, short int month, short int year)
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
	appartment->entryDate = CreateEntryDate(day, month, year);
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
