//
// Created by Ja on 6/15/2025.
//

#include <stdio.h>
#include "genericList.h"
#include "system.h"
#include "row.h"
#include "logger/logger.h"



void listTest() {
	GenericList list_int;
	init_list(&list_int, sizeof(int));

	printf("\na:");
	print_all_data(&list_int);

	int* v1 = add_node(&list_int);
	*v1 = 1;

	printf("\nb:");
	print_all_data(&list_int);

	int* v2 = add_node(&list_int);
	*v2 = 2;

	printf("\nc:");
	print_all_data(&list_int);

	int* v3 = add_node(&list_int);
	*v3 = 3;

	delete_all(&list_int);

	printf("\nd:");
	print_all_data(&list_int);
}

void log_write_all(const uint32 loggerHandle, const char* message) {
	logger_log(loggerHandle, INFO, message);
	logger_log(loggerHandle, DEBUG, message);
	logger_log(loggerHandle, WARNING, message);
	logger_log(loggerHandle, ERR, message);
}

void logTest(const uint32 loggerHandle) {
	set_logger_level(loggerHandle, LOG_INFO);
	log_write_all(loggerHandle, "LOG_INFO");
	set_logger_level(loggerHandle, LOG_ERR);
	log_write_all(loggerHandle, "LOG_ERR");
	set_logger_level(loggerHandle, LOG_DEBUG);
	log_write_all(loggerHandle, "LOG_DEBUG");
	set_logger_level(loggerHandle, LOG_WARNING);
	log_write_all(loggerHandle, "LOG_WARNING");
	set_logger_level(loggerHandle, LOG_INFO | LOG_WARNING | LOG_DEBUG);
	log_write_all(loggerHandle, "LOG_INFO | LOG_WARNING | LOG_DEBUG");
	set_logger_level(loggerHandle, LOG_WARNING | LOG_ERR);
	log_write_all(loggerHandle, "LOG_WARNING | LOG_ERR");
}
