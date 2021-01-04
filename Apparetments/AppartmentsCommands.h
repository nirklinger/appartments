#ifndef APT_COMAND
#define APT_COMAND
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "AppartmentStruct.h"
#include "AppartmentsFile.h"
#include "history.h"

void listen(AppartmentsList *appartments);

char* getNextCommand();

void addAppartment(AppartmentsList *appartments, char *commandString);

void addAppartmentSortedByPrice(AppartmentsList *appartments, Appartment *apt);

void buyAppartment(AppartmentsList *appartments, unsigned int id);

unsigned short int getNewAppartmentCode();

void setLastAppartmentCode(unsigned short int lastCode);

void executeCommand(char* commandString, AppartmentsList *appartments);

void printWelcome();
#endif // APT_COMAND