#ifndef APT_COMAND
#define APT_COMAND

#include "AppartmentStruct.h"
#include "history.h"

void listen(AppartmentsList *appartments);

void addAppartment(AppartmentsList *appartments, char *commandString);

void addAppartmentSortedByPrice(AppartmentsList *appartments, Appartment *apt);

void buyAppartment(AppartmentsList *appartments, unsigned int id);

int getNewAppartmentCode();

void executeCommand(char* commandString, AppartmentsList *appartments);
#endif // APT_COMAND