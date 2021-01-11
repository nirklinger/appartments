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

//Listen to the next command from user
void listen(ApartmentsList *apartments);

char* getNextCommand();

void addApartment(ApartmentsList *apartments, char *commandString);

void addApartmentSortedByPrice(ApartmentsList *apartments, Apartment *apt);

void buyApartment(ApartmentsList *apartments, unsigned int id);

unsigned short int getNewApartmentCode();

void setLastApartmentCode(unsigned short int lastCode);

void executeCommand(char* commandString, ApartmentsList *apartments);

ApartmentNode * findApartment(ApartmentsList* apartments, char* commandString);

//Extract flags with values from find-apt command into an array. Update isAsc pointer accordingly to -s/-sr flags
Flag* getFlagsArray(char* commandString, int* arraySize, BOOL* isAsc);

BOOL checkIfApartmentMatchFlag(Flag flag, Apartment* apartment);

void printApartment(Apartment* apartment);

//If all of the search flags from command match the apartment then print it.
//If an apartment was found to print, update "hasFound".
//Print can be in Asc/Desc order according to isAsc parameter.
void printAptByFlag(ApartmentNode* apartmentNode, Flag* flags, int flagsArraySize, BOOL isAsc, BOOL* Yagshamash);

void printEntryDate(EntryDate* entryDate);

void printDBEntryDate(time_t dbEntryTime);

short int convertMonthToNumber(char* month);

EntryDate* convertCommandDateToEntryDate(int commandDate);

//return true if date1 is before or equal to date2
BOOL isDateInRange(EntryDate date1, EntryDate date2);

BOOL isDBEntryTimeAddedInLastDays(Apartment* apartment, int numberOfDays);

//Delete all apartments added in the last X days
void deleteApartment(ApartmentsList* apartments, int days);

//Delete apprtments added in the last X days.
//Update new tail if needed.
//Returns the new head 
ApartmentNode* deleteApartmentNode(ApartmentNode* apartmentNode, int days, ApartmentNode** newTail);

void printWelcome();
#endif // APT_COMAND