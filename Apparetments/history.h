#ifndef HISTORY
#define HISTORY
#define _CRT_SECURE_NO_WARNINGS
#define N 7
#define HISTORY_FILE "./history.txt"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct historyNode {
	struct historyNode *next;
	char* command;
} HistoryNode;

typedef struct historyList {
	HistoryNode *head;
	HistoryNode *tail;
} HistoryList;

void initHistoryMemory();

bool isEmptyHistoryList(HistoryList* list);

void makeEmptyHistoryList(HistoryList *list);

HistoryNode* createHistoryNode(char* command, HistoryNode* next);

char *makeSpaceForCommand();

void pushNewCommand(char *newCommand);

void pushCommandToLongTermHistory(char *comand);

void shortTermHistory(int startIndex);

int longTermHistory();

char* getCommandFromHistory(char* f);

char* replaceCommandStrings(char* commandToExecute, char* original, char* replace);

void writeShortHistoryCommandsToFile(FILE* historyFile);

void writeLongTermHistoryToFile(FILE *historyFile, HistoryNode *node);

void writeHistoryFile();

void loadHistoryFromoFile();

void LoadNextCommand(FILE *historyFile, char* commandString);
#endif //HISTORY 