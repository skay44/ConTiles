//
// Created by Ja on 5/30/2025.
//
#include "logger.h"

#include <stdio.h>

#include "const.h"

static char file_path[FILE_LENGTH];
static bool file_opened = false;
static FILE* file;

void logger_set_file_path(const char* path){
	if (file_opened) {
		fflush(file);
		fclose(file);
	}
	strncpy(file_path, path, FILE_LENGTH-1);
	file_path[FILE_LENGTH-1] = '\0';
	file = fopen(file_path, "a");
	file_opened = true;
}

void logger_log(const char* data){
	fwrite(data, 1, strlen(data), file);
	fwrite("\n", 1, 1, file);
}
