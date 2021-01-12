#include "ApartmentsCommands.h"

unsigned short int apartmentCode = 0;

void printWelcome()
{
	printf("Please enter one of the following commands:\n");
	printf("add-apt, find-apt, buy-apt, delete-apt or exit\n");
	printf("For reconstruction commands, please enter:\n");
	printf("!!, !num, history, short_history or !num^str1^str2\n");
}

#pragma region addApartments
void addApartmentSortedByPrice(ApartmentsList *apartments, Apartment *apt)
{
	if (isEmptyList(apartments))
	{
		apartments->head = apartments->tail = createApartmentNode(apt, NULL);
		return;
	}

	if (apartments->head->apartment->price >= apt->price)
	{
		ApartmentNode *newHead = createApartmentNode(apt, apartments->head);
		apartments->head = newHead;
		return;
	}

	ApartmentNode *node = apartments->head;

	while (node != apartments->tail && node->next->apartment->price < apt->price)
	{
		node = node->next;
	}

	if (node == apartments->tail)
	{
		node->next = createApartmentNode(apt, NULL);
		apartments->tail = node->next;
	}
	else
	{
		node->next = createApartmentNode(apt, node->next);
	}
}

void addApartment(ApartmentsList *apartments, char *commandString)
{
	char *addressStart = strchr(commandString, '"');
	char *addressEnd = strrchr(commandString, '"');
	unsigned int commandLength = strlen(commandString);
	int price;
	short int rooms, day, month, year;

	char *address = (char*)malloc(commandLength);
	checkFailedMalloc(address);
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

	Apartment *apt = createApartmentWithNowTimestamp(getNewApartmentCode(),
		address, price, rooms, day, month, year);

	addApartmentSortedByPrice(apartments, apt);
}
#pragma endregion addApartments

void buyApartment(ApartmentsList *apartments, unsigned int id)
{
	ApartmentNode *node = apartments->head;

	if (node->apartment->id == id)
	{
		if (apartments->head == apartments->tail)
		{
			makeEmptyApartmentsList(apartments);
		}
		else
		{
			apartments->head = node->next;
		}
		
		freeApartmentNode(node);
		return;
	}
	
	//While next node isn't for buying, go forward
	while (node != apartments->tail && node->next->apartment->id != id)
	{
		node = node->next;
	}

	//If current node at the end of list, it means that the id wasn't found
	if (node == apartments->tail)
	{
		printf("No apartment match id: %d\n", id);
		return;
	}

	//Remove the next node and update the list. If next node is tail then update accordingly
	if (node->next == apartments->tail)
	{
		apartments->tail = node;
		freeApartmentNode(node->next);
		node->next = NULL;
	}
	else
	{
		ApartmentNode *tmp = node->next;
		node->next = node->next->next;
		freeApartmentNode(tmp);
	}
}

void printApartment(Apartment* apartment)
{
	printf("Apt details:\n");
	printf("Code: %hu\n", apartment->id); 
	printf("Address: %s\n", apartment->address);
	printf("Number of rooms: %hi\n", apartment->roomCount); 
	printf("Price: %d\n", apartment->price);
	printf("Entry date: "); 
	printEntryDate(apartment->entryDate);
	printf("Database entry date: ");
	printDBEntryDate(apartment->dbEntryTime);
}

void printEntryDate(EntryDate* entryDate)
{
	printf("%hi.%hi.20%hi\n", entryDate->day, entryDate->month, entryDate->year);
}

void printDBEntryDate(time_t dbEntryTime)
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

ApartmentNode * findApartment(ApartmentsList* apartments, char* commandString) 
{	
	Flag* searchFlags;
	int flagsArraySize;
	BOOL isAsc, hasFound = false;

	searchFlags = getFlagsArray(commandString, &flagsArraySize, &isAsc);
	printAptByFlag(apartments->head, searchFlags, flagsArraySize, isAsc, &hasFound);
	free(searchFlags);

	if (!hasFound)
	{
		printf("Could not find any apartment\n");
	}
}

//If all of the search flags from command match the apartment then print it.
//If an apartment was found to print, update "hasFound".
//Print can be in Asc/Desc order according to isAsc parameter.
void printAptByFlag(ApartmentNode* apartmentNode, Flag* flags, int flagsArraySize, BOOL isAsc, BOOL *hasFound)
{	
	BOOL isApartmentMatchFlag = false;

	if(apartmentNode == NULL){
		return;
	}

	if(!isAsc) {
		printAptByFlag(apartmentNode->next, flags, flagsArraySize, isAsc, hasFound);
	}

	for (int i = 0; i < flagsArraySize; i++)
	{
		isApartmentMatchFlag = checkIfApartmentMatchFlag(flags[i], apartmentNode->apartment);
		if(!isApartmentMatchFlag){
			break;
		}
	}

	if (isApartmentMatchFlag){
		printApartment(apartmentNode->apartment);
		*hasFound = true;
	}

	if(isAsc){
		printAptByFlag(apartmentNode->next, flags, flagsArraySize, isAsc, hasFound);
	}
}

BOOL checkIfApartmentMatchFlag(Flag flag, Apartment* apartment)
{
	if(strcmp(flag.name,"-MaxPrice") == 0){
		return (apartment->price <= flag.value) ? true : false;
	}
	if(strcmp(flag.name,"-MinPrice") == 0) {
		return (apartment->price >= flag.value) ? true : false;
	}
	if(strcmp(flag.name,"-MinNumRooms") == 0){ 
		return (apartment->roomCount >= flag.value) ? true : false;
	}
	if(strcmp(flag.name,"-MaxNumRooms") == 0){
		return (apartment->roomCount <= flag.value) ? true : false;
	}
	if(strcmp(flag.name,"-Date") == 0){
		EntryDate* flagEntryDate = convertCommandDateToEntryDate(flag.value);
		BOOL isApartmentDateMatchFlagDate = isDateInRange(*(apartment->entryDate), *(flagEntryDate));
		return (isApartmentDateMatchFlagDate) ? true : false;
	}
	if(strcmp(flag.name, "-Enter") == 0){
		return (isDBEntryTimeAddedInLastDays(apartment, flag.value)) ? true : false;
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

BOOL isDBEntryTimeAddedInLastDays(Apartment* apartment, int numberOfDays)
{
	time_t nowTime;
	nowTime = time(NULL);
	long long apartmentDBEntryTime = (long long)apartment->dbEntryTime;
	long long currentTime = (long long) nowTime;
	
	return ((currentTime - apartmentDBEntryTime) <= ONE_DAY*numberOfDays);
}

//Extract flags with values from find-apt command into an array. Update isAsc pointer accordingly to -s/-sr flags
Flag* getFlagsArray(char* commandString, int* arraySize, BOOL* isAsc) 
{
	Flag* flags = (Flag*)malloc(sizeof(Flag)*FLAGS_MAX_SIZE);
	checkFailedMalloc(flags);
	char* valueStr;
	char* flagName = strtok(commandString, " ");
	*isAsc = true;
	int i = 0;
	
	//While there are still more "search flags" to extract from the command, store the flags in an array
	while (flagName != NULL)
	{
		//update isAsc accordint to -s/-sr.
		if (flagName[1] == 's') {
			*isAsc = (flagName[2] == 'r') ? false : true;
		}
		else {
			flags[i].name = flagName;
			valueStr = strtok(NULL, " ");
			flags[i].value = atoi(valueStr);
			i++;
		}
		flagName = strtok(NULL, " ");
	}

	*arraySize = i;
	flags = (Flag*)realloc(flags, sizeof(Flag)*(*arraySize));
	return flags;
}

//Delete all apartments added in the last X days
void deleteApartment(ApartmentsList* apartments, int days) 
{
	ApartmentNode* aptToFree;
	
	if(apartments->head == apartments->tail){
		if(isDBEntryTimeAddedInLastDays(apartments->head->apartment, days)){
			aptToFree = apartments->head;
			makeEmptyApartmentsList(apartments);
			freeApartmentNode(aptToFree);
		}
		return;
	} 

	apartments->head = deleteApartmentNode(apartments->head, days, &(apartments->tail));

}

//Delete apprtments added in the last X days - Helper.
//Update new tail if needed.
//Returns the new head 
ApartmentNode* deleteApartmentNode(ApartmentNode* apartmentNode, int days, ApartmentNode** newTail){
	ApartmentNode* aptToFree, *newAptList;

	if(apartmentNode == NULL){
		return NULL;
	}

	newAptList = deleteApartmentNode(apartmentNode->next, days, newTail);
	
	if(isDBEntryTimeAddedInLastDays(apartmentNode->apartment, days)){
		freeApartmentNode(apartmentNode);
		return newAptList;
	}
	else {
		apartmentNode->next = newAptList;
		if(newAptList == NULL){
			*newTail = apartmentNode;
		}
		return apartmentNode;
	}
	
}

unsigned short int getNewApartmentCode()
{
	return ++apartmentCode;
}

void setLastApartmentCode(unsigned short int lastCode)
{
	apartmentCode = lastCode;
}

//Listen to the next command from user
void listen(ApartmentsList *apartments)
{
	char *commandString;	

	while (true)
	{
		commandString = getNextCommand();
		executeCommand(commandString, apartments);
		free(commandString);
	}
}

char* getNextCommand()
{
	char x;
	unsigned int commandLength = 0, currentSize = 2;
	char *nextCommand = (char*)malloc(currentSize);
	checkFailedMalloc(nextCommand);
	printf(">> ");
	
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

void executeCommand(char* commandString, ApartmentsList *apartments)
{
	int len = strlen(commandString);
	char *commandForHistory = (char*)malloc(len+1);
	checkFailedMalloc(commandForHistory);
	strcpy(commandForHistory, commandString);
	commandForHistory[len] = '\0';

	char *f = strtok(commandString, " ");

	if(f == NULL)
	{
		return;
	}
	
	if (strcmp(f, "add-apt") == 0)
	{
		addApartment(apartments, commandString + 8);
		pushNewCommand(commandForHistory);
	}
	else if (strcmp(f, "find-apt") == 0)
	{
		findApartment(apartments, commandString + 9);
		pushNewCommand(commandForHistory);
	}
	else if (strcmp(f, "delete-apt") == 0)
	{
		int days;
		// Remove flag delete-apt
		strtok(NULL, " ");
		//Scan value for the -Enter flag from command
		sscanf(strtok(NULL, " "), "%d", &days);
		deleteApartment(apartments, days);
		pushNewCommand(commandForHistory);
	}
	else if (strcmp(f, "buy-apt") == 0)
	{
		unsigned int id;
		//Scan apartment id to buy from command
		sscanf(strtok(NULL, " "), "%u", &id);
		buyApartment(apartments, id);
		pushNewCommand(commandForHistory);
	}
	else if (strcmp(f, "history") == 0)
	{
		longTermHistory();
		shortTermHistory();
		free(commandForHistory);
	}
	else if (strcmp(f, "short_history") == 0)
	{
		shortTermHistory();
		free(commandForHistory);
	}
	else if (strcmp(f, "exit") == 0)
	{
		printf("Good Bye!");
		writeHistoryFile();
		freeHistory();
		writeApartmentsToBinaryFile(apartments);
		freeApartmentsRecursive(apartments->head);
		exit(0);
	}
	else if (*commandForHistory == '!')
	{
		char *historyCommand = getCommandFromHistory(commandForHistory);
		int len = strlen(historyCommand);
		char *commandToExecute = (char*)malloc(len);
		checkFailedMalloc(commandToExecute);
		strcpy(commandToExecute, historyCommand);
		executeCommand(commandToExecute, apartments);		
	}
}