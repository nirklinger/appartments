#ifndef APT_COMAND
#define APT_COMAND
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "AppartmentStruct.h"
#include "AppartmentsFile.h"
#include "history.h"

#define true 1
#define false 0
typedef int BOOL;

void listen(AppartmentsList *appartments);

char* getNextCommand();

void addAppartment(AppartmentsList *appartments, char *commandString);

void addAppartmentSortedByPrice(AppartmentsList *appartments, Appartment *apt);

void buyAppartment(AppartmentsList *appartments, unsigned int id);

unsigned short int getNewAppartmentCode();

void setLastAppartmentCode(unsigned short int lastCode);

void executeCommand(char* commandString, AppartmentsList *appartments);

AppartmentNode * findApartment(AppartmentsList* appartments, char* commandString);

Flag* getFlagsArray(char* commandString, int* arraySize, BOOL* isAsc);

BOOL checkIfAppartmentMatchFlag(Flag flag, Appartment* appartment);

void printAptByFlag(AppartmentNode* appartmentNode, Flag* flags, int flagsArraySize, BOOL isAsc);

void printEntryDate(EntryDate* entryDate);

void printDBEntryDate(time_t* dbEntryTime);

short int convertMonthToNumber(char* month);

EntryDate* convertCommandDateToEntryDate(int commandDate);

//return true if date1 is before or equal to date2
BOOL isDateInRange(EntryDate date1, EntryDate date2);

BOOL isDBEntryTimeAddedInLastDays(Appartment* appartment, int numberOfDays);

void printWelcome();
#endif // APT_COMAND