#ifndef APT_COMAND
#define APT_COMAND
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "ApartmentStruct.h"
#include "ApartmentsFile.h"
#include "history.h"
#define ONE_DAY 86400

void listen(ApartmentsList *apartments);

char* getNextCommand();

void addApartment(ApartmentsList *apartments, char *commandString);

void addApartmentSortedByPrice(ApartmentsList *apartments, Apartment *apt);

void buyApartment(ApartmentsList *apartments, unsigned int id);

unsigned short int getNewApartmentCode();

void setLastApartmentCode(unsigned short int lastCode);

void executeCommand(char* commandString, ApartmentsList *apartments);

ApartmentNode * findApartment(ApartmentsList* apartments, char* commandString);

Flag* getFlagsArray(char* commandString, int* arraySize, BOOL* isAsc);

BOOL checkIfApartmentMatchFlag(Flag flag, Apartment* apartment);

void printApartment(Apartment* apartment);

void printAptByFlag(ApartmentNode* apartmentNode, Flag* flags, int flagsArraySize, BOOL isAsc, BOOL* Yagshamash);

void printEntryDate(EntryDate* entryDate);

void printDBEntryDate(time_t dbEntryTime);

short int convertMonthToNumber(char* month);

EntryDate* convertCommandDateToEntryDate(int commandDate);

//return true if date1 is before or equal to date2
BOOL isDateInRange(EntryDate date1, EntryDate date2);

BOOL isDBEntryTimeAddedInLastDays(Apartment* apartment, int numberOfDays);

void deleteApartment(ApartmentsList* apartments, int days);

ApartmentNode* deleteApartmentNode(ApartmentNode* apartmentNode, int days, ApartmentNode** newTail);

void printWelcome();
#endif // APT_COMAND