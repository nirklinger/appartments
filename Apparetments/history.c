#define _CRT_SECURE_NO_WARNINGS
#include "history.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define N 7

char *short_term_history[N];
HistoryList long_term_history;

void initHistoryMemory()
{
	for (int i = 0; i < N; i++)
	{
		short_term_history[i] = NULL;
	}

	makeEmptyHistoryList(&long_term_history);
}

bool isEmptyHistoryList(HistoryList* list)
{
	return (list->head == NULL) ? true : false;
}

void makeEmptyHistoryList(HistoryList *list)
{
	list->head = list->tail = NULL;
}

HistoryNode* createHistoryNode(char* command, HistoryNode* next)
{
	HistoryNode *newNode = (HistoryNode*)malloc(sizeof(HistoryNode));
	newNode->command = command;
	newNode->next = next;

	return newNode;
}

char *makeSpaceForCommand()
{
	char *oldest = short_term_history[0];

	for (int i = 0; i < N - 1; i++)
	{
		short_term_history[i] = short_term_history[i + 1];
	}

	return oldest;
}

void pushNewCommand(char *newCommand)
{
	char* transferComand = makeSpaceForCommand();
	unsigned int len = strlen(newCommand);

	short_term_history[N - 1] = newCommand;	

	if (transferComand != NULL)
	{
		pushCommandToLongTermHistory(transferComand);
	}
}

void pushCommandToLongTermHistory(char *comand)
{
	HistoryNode *newHead = createHistoryNode(comand, NULL);

	if (isEmptyHistoryList(&long_term_history))
	{
		long_term_history.head = long_term_history.tail = newHead;
	}
	else
	{
		long_term_history.tail->next = newHead;
		long_term_history.tail = newHead;
	}
}

void shortTermHistory(int startIndex)
{
	for (int i = 0; i < N; i++)
	{
		if (short_term_history[i] == NULL)
		{
			break;
		}

		printf("%d %s\n", startIndex + i, short_term_history[i]);
	}
}

int longTermHistory()
{
	HistoryNode *p = long_term_history.head;
	int i = 1;

	while (p != NULL)
	{
		printf("%d %s\n", i, p->command);
		i++;
		p = p->next;
	}

	return i;
}

char* getCommandFromHistory(char* f)
{
	if (f[1] == '!')
	{
		return short_term_history[N - 1];
	}

	char *replace = strchr(f, '^');

	if (replace == NULL)
	{
		int commandNumber;
		sscanf(f + 1, "%d", &commandNumber);
		
		HistoryNode *p = long_term_history.head;

		int i = 1;

		for (; p != NULL && i < commandNumber; i++)
		{
			p = p->next;
		}

		if(p != NULL)
		{
			return p->command;
		}		

		return short_term_history[commandNumber -i];
	}
}