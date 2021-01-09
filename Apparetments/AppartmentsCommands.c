#include "AppartmentsCommands.h"
#define true 1
#define false 0
typedef int BOOL;


long long ONE_DAY =  86400;
unsigned short int appartmentCode = 0;

void printWelcome()
{
	printf("Please enter one of the following commands:\n");
	printf("add-apt, find-apt, buy-apt, delete-apt or exit\n");
	printf("For reconstruction commands, please enter :\n");
	printf("!!, !num, history, short_history or !num^str1^str2\n");
}

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

	sscanf(addressEnd + 1, "%d %hu %hu %hu %hu",
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

void printAppartment(Appartment* appartment)
{
	printf("Apt details:\n");
	printf("Code: %hu\n", appartment->id); 
	printf("Address: %s\n", appartment->address);
	printf("Number of rooms: %hi\n", appartment->roomCount); 
	printf("Price: %d\n", appartment->price);
	printf("Entry date: "); 
	printEntryDate(appartment->entryDate);
	printf("Database entry date: ");
	printDBEntryDate(appartment->dbEntryTime);
}

void printEntryDate(EntryDate* entryDate)
{
	printf("%hi.%hi.20%hi\n", entryDate->day, entryDate->month, entryDate->year);
}

void printDBEntryDate(time_t* dbEntryTime)
{
	char* dbEntryTimeInCTimeSyntax = ctime(&dbEntryTime);
	//Remove week day string
	strtok(dbEntryTimeInCTimeSyntax, " ");
	//Convert month name into number
	char* monthString =  strtok(NULL, " ");
	short int month = convertMonthToNumber(monthString);
	//Exctract day
	char* day = strtok(NULL, " ");
	//Remove clock time
	strtok(NULL, " ");
	//Exctract year, the year alreay includes '\n' so no need to add when printing.
	char* year = strtok(NULL, " ");
	printf("%s.%hi.%s", day, month, year);	
}

short int convertMonthToNumber(char* month) 
{
	if (strcmp(month, "Jan") == 0) {return 1;}
	if (strcmp(month, "Feb") == 0) {return 2;}
	if (strcmp(month, "Mar") == 0) {return 3;}
	if (strcmp(month, "Apr") == 0) {return 4;}
	if (strcmp(month, "May") == 0) {return 5;}
	if (strcmp(month, "Jun") == 0) {return 6;}
	if (strcmp(month, "Jul") == 0) {return 7;}
	if (strcmp(month, "Agu") == 0) {return 8;}
	if (strcmp(month, "Sep") == 0) {return 9;}
	if (strcmp(month, "Oct") == 0) {return 10;}
	if (strcmp(month, "Nov") == 0) {return 11;}
	if (strcmp(month, "Dec") == 0) {return 12;}
	return 0;
}

AppartmentNode * findApartment(AppartmentsList* appartments, char* commandString) 
{	
	Flag* flags;
	int flagsArraySize;
	BOOL isAsc;
	flags = getFlagsArray(commandString, &flagsArraySize, &isAsc);
	printAptByFlag(appartments->head, flags, flagsArraySize, isAsc);
}

void printAptByFlag(AppartmentNode* appartmentNode, Flag* flags, int flagsArraySize, BOOL isAsc)
{	
	BOOL isAppartmentMatchFlag;

	//is Empty list
	if(appartmentNode == NULL){
		return;
	}

	if(!isAsc) {
		printAptByFlag(appartmentNode->next, flags, flagsArraySize, isAsc);
	}

	//TODO: into method
	for (int i = 0; i < flagsArraySize; i++)
	{
		isAppartmentMatchFlag = checkIfAppartmentMatchFlag(flags[i], appartmentNode->appartment);
		if(!isAppartmentMatchFlag){
			break;
		}
		else if (i == (flagsArraySize -1)) {
			printAppartment(appartmentNode->appartment);
		}

	}

	if(isAsc){
		printAptByFlag(appartmentNode->next, flags, flagsArraySize, isAsc);
	}
}

BOOL checkIfAppartmentMatchFlag(Flag flag, Appartment* appartment)
{
	if(strcmp(flag.name,"-MaxPrice") == 0){
		return (appartment->price <= flag.value) ? true : false;
	}
	if(strcmp(flag.name,"-MinPrice") == 0) {
		return (appartment->price >= flag.value) ? true : false;
	}
	if(strcmp(flag.name,"-MinNumRooms") == 0){ 
		return (appartment->roomCount >= flag.value) ? true : false;
	}
	if(strcmp(flag.name,"-MaxNumRooms") == 0){
		return (appartment->roomCount <= flag.value) ? true : false;
	}
	if(strcmp(flag.name,"-Date") == 0){
		EntryDate* flagEntryDate = convertCommandDateToEntryDate(flag.value);
		BOOL isAppartmentDateMatchFlagDate = isDateInRange(*(appartment->entryDate), *(flagEntryDate));
		return (isAppartmentDateMatchFlagDate) ? true : false;
	}
	if(strcmp(flag.name, "-Enter") == 0){
		return (isDBEntryTimeAddedInLastDays(appartment, flag.value)) ? true : false;
	}
	if((strcmp(flag.name, "-s") == 0) || (strcmp(flag.name, "-sr") == 0) ){
		return true;
	}
	return false;
}

EntryDate* convertCommandDateToEntryDate(int commandDate)
{
	short int day, month, year;
	
	day = (short)(commandDate/1000000);
	commandDate = commandDate%1000000;
	month = (short)(commandDate/10000);
	year = (short)(commandDate%100);
	
	return createEntryDate(day, month, year);
}

//return true if date1 is before or equal to date2
BOOL isDateInRange(EntryDate date1, EntryDate date2)
{
	if ((date1.year == date2.year)&&(date1.month == date2.month)&&(date1.day == date2.day)){
		return true;
	}

	if (date1.year < date2.year){
		return true;
	}

	if(date1.year > date2.year){
		return false;
	}
	
	if (date1.month < date2.month){
		return true;
	}

	if (date1.month > date2.month){
		return false;
	}
	return (date1.day < date2.day) ? true : false ;	
}

BOOL isDBEntryTimeAddedInLastDays(Appartment* appartment, int numberOfDays)
{
	time_t nowTime;
	nowTime = time(NULL);
	long long appartmentDBEntryTime = (long long)appartment->dbEntryTime;
	long long currentTime = (long long) nowTime;
	
	return ((currentTime - appartmentDBEntryTime) <= ONE_DAY*numberOfDays);
}

Flag* getFlagsArray(char* commandString, int* arraySize, BOOL* isAsc) 
{
	unsigned int commandLength = strlen(commandString);
	unsigned int usedPartOfCommandLength;
	int flagsArraySize = 0;
	Flag* flag = (Flag*)malloc(sizeof(Flag)*10);
	int i = 0;
	char* valueStr;
	flag[i].name = strtok(commandString, " ");
	*isAsc = true;
	
	while (commandLength > 0)
	{
		flagsArraySize++;
		if (flag[i].name[1] == 's') { //realing on sr and s flags being at the end
			flag[i].value = NULL;
			*arraySize = flagsArraySize;
			*isAsc = (flag[i].name[2] == 'r') ? false : true;
			return flag;
		}
		
		valueStr = strtok(NULL, " ");
		flag[i].value = atoi(valueStr);
		
		
		usedPartOfCommandLength = 1 + strlen(flag[i].name) + strlen(valueStr);
		commandLength = (commandLength >= usedPartOfCommandLength)? commandLength - usedPartOfCommandLength : 0;
		i++;
		if (commandLength > 0) {
			flag[i].name = strtok(NULL, " ");
			commandLength--;
		}
	}

	*arraySize = flagsArraySize;
	return flag;
}

unsigned short int getNewAppartmentCode()
{
	return ++appartmentCode;
}

void setLastAppartmentCode(unsigned short int lastCode)
{
	appartmentCode = lastCode;
}

void listen(AppartmentsList *appartments)
{
	char *commandString;	

	while (true)
	{
		commandString = getNextCommand();
		executeCommand(commandString, appartments);
	}
}

char* getNextCommand()
{
	char x;
	unsigned int commandLength = 0, currentSize = 2;
	char *nextCommand = (char*)malloc(currentSize);
	
	while (x = getchar())
	{
		if (x == '\n' || x == '\0')
		{
			nextCommand = realloc(nextCommand, commandLength+1);
			nextCommand[commandLength] = '\0';
			return nextCommand;
		}			
		else
		{
			if (commandLength >= currentSize)
			{
				currentSize *= 2;
				nextCommand = realloc(nextCommand, currentSize);
			}
			
			nextCommand[commandLength++] = x;
		}			
	}

	return nextCommand;
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
		findApartment(appartments, commandString + 9);
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
		writeAppartmentsToBinaryFile(appartments);
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