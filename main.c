#include <stdio.h>
#include "genericList.h"
#include "system.h"
#include "column.h"
#include "row.h"
#include "screen.h"
#include "logger/logger.h"
#include <signal.h>


void listTest() {
	GenericList list_int;
	initList(&list_int, sizeof(int));

	printf("\na:");
	printAllData(&list_int);

	int* v1 = addNode(&list_int);
	*v1 = 1;

	printf("\nb:");
	printAllData(&list_int);

	int* v2 = addNode(&list_int);
	*v2 = 2;

	printf("\nc:");
	printAllData(&list_int);

	int* v3 = addNode(&list_int);
	*v3 = 3;

	deleteAll(&list_int);

	printf("\nd:");
	printAllData(&list_int);
}

void demoLayout(Screen* mainScreen) {
	addColumnToScreen(mainScreen, 1, 0x1, 0x10);
	addColumnToScreen(mainScreen, 5, 0x2, 0x20);
	Column* red_column = addColumnToScreen(mainScreen, 3, 0x4, 0x40);

	addRowToColumn(red_column, 2, 0x1, 0x10);
	addRowToColumn(red_column, 2, 0x2, 0x20);
	addRowToColumn(red_column, 4, 0x4, 0x40);
}

void sigint_handler(int sigNum) {
	clearScreen();
	exit(0);
}

uint32 DEFAULT_LOGGER;

int main(void) {
	signal(SIGINT, sigint_handler);
	init_loggers();

	DEFAULT_LOGGER = get_new_logger();
	logger_set_file_path(DEFAULT_LOGGER,"log.txt");

	Screen mainScreen;
	initializeScreen(&mainScreen);
	demoLayout(&mainScreen);

	while (1) {
		logger_log(DEFAULT_LOGGER, "someLogs", INFO);
		generateView(&mainScreen);
	}
}
