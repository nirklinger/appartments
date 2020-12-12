#ifndef HISTORY
#define HISTORY
#include <stdbool.h>

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
#endif //HISTORY 