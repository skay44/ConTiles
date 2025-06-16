#include "variables.h"

uint32 DEFAULT_LOGGER;

#include "system.h"
#include "column.h"
#include "screen.h"
#include "logger/logger.h"
#include <signal.h>
#include "testing.c"


void demoLayout(Screen* mainScreen) {
	add_column_to_screen(mainScreen, 1, 0x1, 0x10);
	add_column_to_screen(mainScreen, 5, 0x2, 0x20);
	Column* red_column = add_column_to_screen(mainScreen, 3, 0x4, 0x40);

	add_row_to_column(red_column, 2, 0x1, 0x10);
	add_row_to_column(red_column, 2, 0x2, 0x20);
	add_row_to_column(red_column, 4, 0x4, 0x40);
}

void sigint_handler(int sigNum) {
	clear_screen();
	exit(0);
}



int main(void) {
	signal(SIGINT, sigint_handler);
	init_loggers();

	DEFAULT_LOGGER = logger_new();
	set_logger_as_default(DEFAULT_LOGGER);
	set_logger_path(DEFAULT_LOGGER,"log.txt");

	Screen mainScreen;
	initialize_screen(&mainScreen);
	demoLayout(&mainScreen);


	while (1) {
		generate_view(&mainScreen);
	}
}
