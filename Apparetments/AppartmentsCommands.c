#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "AppartmentsCommands.h"

int appartmentCode = 0;

#pragma region addAppartments
void addAppartmentSortedByPrice(AppartmentsList *appartments, Appartment *apt)
{
	if (isEmptyList(appartments))
	{
		appartments->head = appartments->tail = createAppartmentNode(apt, NULL);
		return;
	}

	if (appartments->head->appartment->price >= apt->price)
	{
		AppartmentNode *newHead = createAppartmentNode(apt, appartments->head);
		appartments->head = newHead;
		return;
	}

	AppartmentNode *node = appartments->head;

	while (node != appartments->tail && node->next->appartment->price < apt->price)
	{
		node = node->next;
	}

	if (node == appartments->tail)
	{
		node->next = createAppartmentNode(apt, NULL);
		appartments->tail = node->next;
	}
	else
	{
		node->next = createAppartmentNode(apt, node->next);
	}
}

void addAppartment(AppartmentsList *appartments, char *commandString)
{
	char *addressStart = strchr(commandString, '"');
	char *addressEnd = strrchr(commandString, '"');
	unsigned int commandLength = strlen(commandString);
	int price;
	short int rooms, day, month, year;

	char *address = (char*)malloc(commandLength);
	char *p = addressStart + 1;
	int i = 0;

	while (p != addressEnd)
	{
		address[i] = *p;
		i++;
		p++;
	}

	address[i] = '\0';
	realloc(address, i + 1);

	sscanf(addressEnd + 1, "%d %hi %hi %hi %hi",
		&price, &rooms, &day, &month, &year);

	Appartment *apt = createAppartmentWithNowTimestamp(getNewAppartmentCode(),
		address, price, rooms, day, month, year);

	addAppartmentSortedByPrice(appartments, apt);
}
#pragma endregion addAppartments

void buyAppartment(AppartmentsList *appartments, unsigned int id)
{
	AppartmentNode *node = appartments->head;

	if (node->appartment->id == id)
	{
		if (appartments->head == appartments->tail)
		{
			makeEmptyAppartmentsList(appartments);
		}
		else
		{
			appartments->head = node->next;
		}
		
		freeAppartmentNode(node);
		return;
	}
	
	while (node != appartments->tail && node->next->appartment->id != id)
	{
		node = node->next;
	}

	if (node == appartments->tail)
	{
		return;
	}

	if (node->next == appartments->tail)
	{
		appartments->tail = node;
		freeAppartmentNode(node->next);
		node->next = NULL;
	}
	else
	{
		AppartmentNode *tmp = node->next;
		node->next = node->next->next;
		freeAppartmentNode(tmp);
	}
}

int getNewAppartmentCode()
{
	return ++appartmentCode;
}

void listen(AppartmentsList *appartments)
{
	char commandString[200];	

	while (true)
	{
		gets(commandString);
		executeCommand(commandString, appartments);
	}
}

void executeCommand(char* commandString, AppartmentsList *appartments)
{
	int len = strlen(commandString);
	char *commandForHistory = (char*)malloc(len);
	strcpy(commandForHistory, commandString);

	char *f = strtok(commandString, " ");

	if(f == NULL)
	{
		return;
	}
	
	if (strcmp(f, "add-apt") == 0)
	{
		addAppartment(appartments, commandString + 8);
		pushNewCommand(commandForHistory);
	}
	else if (strcmp(f, "find-apt") == 0)
	{
		printf("find %s\n", f);
		pushNewCommand(commandForHistory);
	}
	else if (strcmp(f, "delete-apt") == 0)
	{
		printf("delete %s\n", f);
		pushNewCommand(commandForHistory);
	}
	else if (strcmp(f, "buy-apt") == 0)
	{
		unsigned int id;
		sscanf(strtok(NULL, " "), "%u", &id);
		buyAppartment(appartments, id);
		pushNewCommand(commandForHistory);
	}
	else if (strcmp(f, "history") == 0)
	{
		int count = longTermHistory();
		shortTermHistory(count);
		pushNewCommand(commandForHistory);
	}
	else if (strcmp(f, "short_history") == 0)
	{
		shortTermHistory(1);
		pushNewCommand(commandForHistory);
	}
	else if (strcmp(f, "exit") == 0)
	{
		printf("Bye Bye!");
		writeHistoryFile();
		exit(0);
	}
	else if (*commandForHistory == '!')
	{
		char *historyCommand = getCommandFromHistory(commandForHistory);
		int len = strlen(historyCommand);
		char *commandToExecute = (char*)malloc(len);
		strcpy(commandToExecute, historyCommand);
		executeCommand(commandToExecute, appartments);		
	}
}