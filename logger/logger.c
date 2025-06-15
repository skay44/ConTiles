//
// Created by Ja on 5/30/2025.
//
#include "logger.h"

#include <genericVector.h>
#include <variables.h>
#include <time.h>
#include <sys/time.h>

#define LOGGER_INIT { .file_path = {0}, .file_opened = false, .file = NULL }

static GenericVector loggerVector;
static time_t rawtime;
static struct tm* timeinfo;

void init_loggers() {
	gv_init_vector(&loggerVector, sizeof(Logger));
}

uint32 get_new_logger() {
	Logger* logger = malloc(sizeof(*logger));
	if (logger) {
		*logger = (Logger)LOGGER_INIT;  // Apply default initialization
	}

	const uint32 toInsertAt = loggerVector.size;
	gv_push_back(&loggerVector, logger);
	return toInsertAt;
}

void logger_set_file_path(const uint32 handle,const char* path){
	const auto logger = (Logger*)gv_get_at(&loggerVector,handle);
	if (logger->file_opened) {
		fflush(logger->file);
		fclose(logger->file);
	}
	strncpy(logger->file_path, path, FILE_LENGTH-1);
	logger->file_path[FILE_LENGTH-1] = '\0';
	logger->file = fopen(logger->file_path, "a");
	logger->file_opened = true;
}

char* log_type_to_str(const LogType log) {
	switch (log) {
		case INFO:
			return "INFO: ";
		case DEBUG:
			return "DEBUG: ";
		case WARNING:
			return "WARNING: ";
		case ERR:
			return "ERR: " ;
		default:
			return "Unknown: ";
	}
}

void logger_log(const uint32 handle,const char* data, const LogType log_type){
	const auto logger = (Logger*)gv_get_at(&loggerVector,handle);

	time_t rawtime;
	struct tm * timeinfo;

	struct timeval timesecs;
	gettimeofday(&timesecs, NULL);

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );

	fprintf(logger->file,
		"%d/%d/%d [%02d:%02d:%02d:%06d] ",
		timeinfo->tm_year+1900,
		timeinfo->tm_mon,
		timeinfo->tm_mday,
		timeinfo->tm_hour,
		timeinfo->tm_min,
		timeinfo->tm_sec,
		timesecs.tv_usec);

	char* logtypestr = log_type_to_str(log_type);

	fwrite(logtypestr, 1, strlen(logtypestr), logger->file);

	fwrite(data, 1, strlen(data), logger->file);
	fwrite("\n", 1, 1, logger->file);
}
