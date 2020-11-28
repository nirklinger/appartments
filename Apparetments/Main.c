#define _CRT_SECURE_NO_WARNINGS
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "AppartmentStruct.c"

void listen(AppartmentsList *appartments);

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

void listen(AppartmentsList *appartments)
{
	char commandString[200];

	while (true)
	{
		gets(commandString);

		char *f = strtok(commandString, " ");

		if (strcmp(f, "add-apt") == 0)
		{
			printf("add %s", f);
		}
		else if (strcmp(f, "find-apt") == 0)
		{
			printf("find %s", f);
		}
		else if (strcmp(f, "delete-apt") == 0)
		{
			printf("delete %s", f);
		}
		else if (strcmp(f, "buy-apt") == 0)
		{
			printf("buy %s", f);
		}
		else if (strcmp(f, "history") == 0)
		{
			printf("history %s", f);
		}
		else if (strcmp(f, "short_history") == 0)
		{
			printf("short %s", f);
		}
		else if (strcmp(f, "exit") == 0)
		{
			printf("exit %s", f);
		}
		else if (*f == '!')
		{
			printf("!!!!!!! %s", f);
		}
	}
}

