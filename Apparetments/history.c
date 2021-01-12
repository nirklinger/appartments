#include "history.h"

char *short_term_history[N];
HistoryList long_term_history;
unsigned int longHistoryCounter = 0;

void initHistoryMemory()
{
	for (int i = 0; i < N; i++)
	{
		short_term_history[i] = NULL;
	}

	makeEmptyHistoryList(&long_term_history);
}

BOOL isEmptyHistoryList(HistoryList* list)
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
	checkFailedMalloc(newNode);	
	newNode->command = command;
	newNode->next = next;

	return newNode;
}

//Make space in short term history array for the new command
char *makeSpaceForCommand()
{
	char *oldest = short_term_history[0];

	for (int i = 0; i < N - 1; i++)
	{
		short_term_history[i] = short_term_history[i + 1];
	}

	return oldest;
}

//Push the new command to both short and long term history
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
	HistoryNode *newTail = createHistoryNode(comand, NULL);

	if (isEmptyHistoryList(&long_term_history))
	{
		long_term_history.head = long_term_history.tail = newTail;
	}
	else
	{
		long_term_history.tail->next = newTail;
		long_term_history.tail = newTail;
	}

	longHistoryCounter++;
}

void shortTermHistory()
{
	for (int i = 0; i < N; i++)
	{
		if (short_term_history[i] == NULL)
		{
			break;
		}

		printf("%d: %s\n", 1 + longHistoryCounter + i, short_term_history[i]);
	}
}

void longTermHistory()
{
	HistoryNode *p = long_term_history.head;
	int i = 1;

	while (p != NULL)
	{
		printf("%d: %s\n", i, p->command);
		i++;
		p = p->next;
	}
}

char* getCommandFromHistory(char* f)
{
	if (f[1] == '!')
	{
		return short_term_history[N - 1];
	}

	char *commandToExecute;
	char *commandNumberString = strtok(f + 1, "^");
	char *original = strtok(NULL, "^");
	char *replace = strtok(NULL, "^");


	int commandNumber;
	sscanf(commandNumberString, "%d", &commandNumber);

	HistoryNode *p = long_term_history.head;

	int i = 1;

	for (; p != NULL && i < commandNumber; i++)
	{
		p = p->next;
	}

	if (p != NULL)
	{
		commandToExecute = p->command;
	}
	else if(commandNumber - i < N){
		commandToExecute = short_term_history[commandNumber - i];
	}
	else
	{
		printf("Command number doesn't exists in history\n");
		return " ";
	}


	if (original == NULL)
	{
		return commandToExecute;
	}

	return replaceCommandStrings(commandToExecute, original, replace);	
}

char* replaceCommandStrings(char* commandToExecute, char* original, char* replace)
{
	const unsigned int commandLength = strlen(commandToExecute);
	const unsigned int originalLen = strlen(original);
	const unsigned int replaceLen = strlen(replace);

	char* p1 = strstr(commandToExecute, original);

	if(p1 == NULL)
	{
		return commandToExecute;
	}
	
	unsigned int startLength = commandLength - strlen(p1);
	char *replacedCommandToExecute = (char*)malloc
	(commandLength - originalLen + replaceLen + 1);
	checkFailedMalloc(replacedCommandToExecute);
	strncpy(replacedCommandToExecute, commandToExecute, startLength);
	replacedCommandToExecute[startLength] = '\0';
	strcat(replacedCommandToExecute, replace);
	strcat(replacedCommandToExecute, commandToExecute + startLength + originalLen);
	
	return replacedCommandToExecute;
}

void writeHistoryFile()
{
	FILE* historyFile = fopen(HISTORY_FILE, "w");
	checkFailedFileOpen(historyFile);

	writeShortHistoryCommandsToFile(historyFile);
	
	if(!isEmptyHistoryList(&long_term_history))
	{
		writeLongTermHistoryToFile(historyFile, long_term_history.head);
	}	

	fclose(historyFile);
}

void writeLongTermHistoryToFile(FILE *historyFile, HistoryNode *node)
{
	if(node == NULL)
	{
		return;
	}

	writeLongTermHistoryToFile(historyFile, node->next);
	fprintf(historyFile, "%s\n", node->command);
}

void writeShortHistoryCommandsToFile(FILE* historyFile)
{
	for (int i = N-1; i >= 0 ; i--)
	{
		if(short_term_history[i] != NULL)
		{
			fprintf(historyFile, "%s\n", short_term_history[i]);
		}
	}
}

void loadHistoryFromFile()
{
	FILE* historyFile = fopen(HISTORY_FILE, "r");

	if(historyFile == NULL)
	{
		return;
	}
	
	char commandString[256];
	fgets(commandString, 256, historyFile);

	LoadNextCommand(historyFile, commandString);

	fclose(historyFile);
}

void LoadNextCommand(FILE *historyFile, char* commandString)
{
	if (!feof(historyFile))
	{
		char *historyCommand = _strdup(commandString);
		fgets(commandString, 256, historyFile);
		LoadNextCommand(historyFile, commandString);
		pushNewCommand(strtok(historyCommand, "\n"));
	}
}