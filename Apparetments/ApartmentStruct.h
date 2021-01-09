#ifndef APT_STRUCT
#define APT_STRUCT
#include <time.h>
#include <stdlib.h>
#include "utils.h"

typedef struct entryDate {
	short int day;
	short int month;
	short int year;
} EntryDate;

typedef struct apartment {
	unsigned short int id;
	char* address;
	int price;
	short int roomCount;
	EntryDate *entryDate;
	time_t dbEntryTime;
} Apartment;

typedef struct apartmentNode {
	struct apartmentNode *next;
	Apartment *apartment;
} ApartmentNode;

typedef struct apartmentsList {
	ApartmentNode *head;
	ApartmentNode *tail;
} ApartmentsList;

typedef struct flagStruct {
	char* name;
	int value;
} Flag;

void makeEmptyApartmentsList(ApartmentsList *aptList);

BOOL isEmptyList(ApartmentsList *apartments);

ApartmentNode* createApartmentNode(Apartment *apt, ApartmentNode *next);

EntryDate* createEntryDate(short int day, short int month, short int year);

Apartment* createApartment(unsigned short int id, char* address, int price,
	short int roomCount, short int day, short int month, short int year, time_t dbEntryTime);

Apartment* createApartmentWithNowTimestamp(unsigned short int id, char* address, int price,
	short int roomCount, short int day, short int month, short int year);

void freeApartment(Apartment * apt);

void freeApartmentNode(ApartmentNode *node);

#endif // APT_STRUCT