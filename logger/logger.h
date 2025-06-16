//
// Created by Skay44 on 5/30/2025.
//

#ifndef LOGGER_H
#define LOGGER_H

#include <genericVector.h>
#include "variables.h"
#include "const.h"
#include <stdio.h>

typedef enum {
	INFO,
	DEBUG,
	WARNING,
	ERR
} LogType;

#define LOG_INFO 0x1
#define LOG_DEBUG 0x2
#define LOG_WARNING 0x4
#define LOG_ERR 0x8

typedef struct {
	char file_path[FILE_LENGTH];
	bool file_opened;
	FILE* file;
	char log_level;
} Logger;

#define LOGGER_INIT { .file_path = {0}, .file_opened = false, .file = NULL, .log_level = LOG_INFO | LOG_DEBUG | LOG_WARNING | LOG_ERR }

static GenericVector g_loggers;
static uint32 g_default_logger;
static bool g_default_logger_set = false;

void init_loggers();

uint32 logger_new();

void set_logger_path(uint32 handle, const char* path);

void logger_log(uint32 handle, LogType log_type, const char* data, ...);

void set_logger_level(uint32 handle, char log_level);

void set_logger_as_default(uint32 handle);

void set_logger_path_auto(char* path);

void logger_log_auto(LogType log_type, const char* data, ...);

void set_logger_level_auto(char log_level);

#endif //LOGGER_H
