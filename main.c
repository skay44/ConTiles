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

void handle_arguments(int argc, char** argv) {
	if (argc > 1) {
		if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
			printf("ConTiles Version 0.0.1\n");
		}
		if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
			printf("Usage: %s [OPTION]\n"
				   "ConTiles - Console tiling manager\n\n"
				   "Options:\n"
				   "  -h, --help		Display this help message\n"
				   "  -v, --version		Display version information\n",
				   argv[0]);
		}
		exit(0);
	}
}

int main(int argc, char** argv) {
	handle_arguments(argc, argv);

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
