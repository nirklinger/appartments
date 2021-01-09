#ifndef APT_STRUCT
#define APT_STRUCT
#include <time.h>
#include <stdbool.h>

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

typedef struct flagStruct {
	char* name;
	int value;
} Flag;

void makeEmptyAppartmentsList(AppartmentsList *aptList);

bool isEmptyList(AppartmentsList *appartments);

AppartmentNode* createAppartmentNode(Appartment *apt, AppartmentNode *next);

EntryDate* createEntryDate(short int day, short int month, short int year);

Appartment* createAppartment(unsigned int id, char* address, int price,
	short int roomCount, short int day, short int month, short int year, time_t dbEntryTime);

Appartment* createAppartmentWithNowTimestamp(unsigned int id, char* address, int price,
	short int roomCount, short int day, short int month, short int year);

void freeAppartment(Appartment * apt);

void freeAppartmentNode(AppartmentNode *node);

#endif // APT_STRUCT