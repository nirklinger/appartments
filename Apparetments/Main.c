#define _CRT_SECURE_NO_WARNINGS
#include "AppartmentsCommands.h"
#include "AppartmentStruct.h"
#include "history.h"

void main()
{	
	AppartmentsList appartments;
	makeEmptyAppartmentsList(&appartments);	
	initHistoryMemory();
	loadHistoryFromFile();
	loadAppartmentsFromFile(&appartments);
	printWelcome();
	listen(&appartments);
}

