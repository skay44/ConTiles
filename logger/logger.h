//
// Created by Ja on 5/30/2025.
//

#ifndef LOGGER_H
#define LOGGER_H

#include "variables.h"
#include "const.h"
#include <stdio.h>

typedef enum {
	INFO,
	DEBUG,
	WARNING,
	ERR
} LogType;

typedef struct {
	char file_path[FILE_LENGTH];
	bool file_opened;
	FILE* file;
} Logger;

//TODO add handle to function definition, make it so that there can be multiple loggers
void init_loggers();
uint32 get_new_logger();
void logger_set_file_path(uint32 handle, const char* path);
void logger_log(uint32 handle,const char* data,LogType log_type);


#endif //LOGGER_H
