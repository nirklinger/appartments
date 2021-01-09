#ifndef APT_COMAND
#define APT_COMAND

#include "AppartmentStruct.h"
#include "history.h"

#define true 1
#define false 0
typedef int BOOL;

void listen(AppartmentsList *appartments);

void addAppartment(AppartmentsList *appartments, char *commandString);

void addAppartmentSortedByPrice(AppartmentsList *appartments, Appartment *apt);

void buyAppartment(AppartmentsList *appartments, unsigned int id);

int getNewAppartmentCode();

void executeCommand(char* commandString, AppartmentsList *appartments);

AppartmentNode * findApartment(AppartmentsList* appartments, char* commandString);

Flag* getFlagsArray(char* commandString, int* arraySize, BOOL* isAsc);

BOOL checkIfAppartmentMatchFlag(Flag flag, Appartment* appartment);

void printAptByFlag(AppartmentNode* appartmentNode, Flag* flags, int flagsArraySize, BOOL isAsc);

void printEntryDate(EntryDate* entryDate);

void printDBEntryDate(time_t* dbEntryTime);

int convertMonthToNumber(char* month);

EntryDate* convertCommandDateToEntryDate(int commandDate);

//return true if date1 is before or equal to date2
BOOL isDateInRange(EntryDate date1, EntryDate date2);

BOOL isDBEntryTimeAddedInLastDays(Appartment* appartment, int numberOfDays);

#endif // APT_COMAND