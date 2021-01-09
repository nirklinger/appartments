#define _CRT_SECURE_NO_WARNINGS
#include "ApartmentsCommands.h"
#include "ApartmentStruct.h"
#include "history.h"

void main()
{	
	ApartmentsList apartments;
	makeEmptyApartmentsList(&apartments);	
	initHistoryMemory();
	loadHistoryFromFile();
	loadApartmentsFromFile(&apartments);
	printWelcome();
	listen(&apartments);
}

