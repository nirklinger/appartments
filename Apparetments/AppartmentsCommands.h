#ifndef APT_COMAND
#define APT_COMAND

#include "AppartmentStruct.h"

void listen(AppartmentsList *appartments);

void addAppartment(AppartmentsList *appartments, char *commandString);

void addAppartmentSortedByPrice(AppartmentsList *appartments, Appartment *apt);

void buyAppartment(AppartmentsList *appartments, unsigned int id);

int getNewAppartmentCode();

#endif // APT_COMAND