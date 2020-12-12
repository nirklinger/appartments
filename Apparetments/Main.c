#define _CRT_SECURE_NO_WARNINGS
#include "AppartmentsCommands.h"
#include "AppartmentStruct.h"

void main()
{
	AppartmentsList appartments;
	makeEmptyAppartmentsList(&appartments);
	// TODO: load apt binary
	// TODO: load command history
	listen(&appartments);
	// TODO: write apt binary
	// TODO: write command history
}

