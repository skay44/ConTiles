//
// Created by Skay44 on 5/30/2025.
//

#include "logger.h"
#include <variables.h>
#include <time.h>
#include <sys/time.h>

inline void init_loggers() {
	gv_init_vector(&g_loggers, sizeof(Logger));
}

uint32 logger_new() {
	Logger* logger = malloc(sizeof(*logger));
	if (logger) {
		*logger = (Logger)LOGGER_INIT; // Apply default initialization
	}

	const uint32 toInsertAt = g_loggers.size;
	gv_push_back(&g_loggers, logger);
	return toInsertAt;
}

void set_logger_path(const uint32 handle, const char* path) {
	const auto logger = (Logger *) gv_get_at(&g_loggers, handle);
	if (logger->file_opened) {
		fflush(logger->file);
		fclose(logger->file);
	}
	strncpy(logger->file_path, path, FILE_LENGTH - 1);
	logger->file_path[FILE_LENGTH - 1] = '\0';
	logger->file = fopen(logger->file_path, "a");
	logger->file_opened = true;
}

static char* log_type_to_str(const LogType log) {
	switch (log) {
		case INFO:
			return "INFO: ";
		case DEBUG:
			return "DEBUG: ";
		case WARNING:
			return "WARNING: ";
		case ERR:
			return "ERR: ";
		default:
			return "Unknown: ";
	}
}

static bool check_if_should_log(const LogType log_type, const char log_level) {
	switch (log_type) {
		case INFO:
			return (log_level & LOG_INFO) == LOG_INFO;
		case DEBUG:
			return (log_level & LOG_DEBUG) == LOG_DEBUG;
		case WARNING:
			return (log_level & LOG_WARNING) == LOG_WARNING;
		case ERR:
			return (log_level & LOG_ERR) == LOG_ERR;
		default:
			return false;
	}
}

void logger_log_v(const Logger* logger, const LogType log_type, const char* data, const va_list args) {
	time_t rawtime;
	struct tm* timeinfo;
	struct timeval timesecs;
	gettimeofday(&timesecs, NULL);
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	fprintf(logger->file,
	        "%d/%d/%d [%02d:%02d:%02d:%06d] ",
	        timeinfo->tm_year + 1900,
	        timeinfo->tm_mon,
	        timeinfo->tm_mday,
	        timeinfo->tm_hour,
	        timeinfo->tm_min,
	        timeinfo->tm_sec,
	        timesecs.tv_usec);

	char* logtypestr = log_type_to_str(log_type);
	fwrite(logtypestr, 1, strlen(logtypestr), logger->file);

	vfprintf(logger->file, data, args);

	fwrite("\n", 1, 1, logger->file);
}


void logger_log(const uint32 handle, const LogType log_type, const char* data, ...) {
	if (!data) return;
	const auto logger = (Logger *) gv_get_at(&g_loggers, handle);
	if (!check_if_should_log(log_type, logger->log_level)) {
		return;
	}

	va_list args;
	va_start(args, data);
	logger_log_v(logger, log_type, data, args);
	va_end(args);
}

inline void set_logger_level(const uint32 handle, const char log_level) {
	const auto logger = (Logger *) gv_get_at(&g_loggers, handle);
	logger->log_level = log_level;
}

void set_logger_as_default(const uint32 handle) {
	g_default_logger = handle;
	g_default_logger_set = true;
}

void set_logger_path_auto(char* path) {
	if (g_default_logger_set) {
		set_logger_path(g_default_logger, path);
	}
}

void logger_log_auto(const LogType log_type, const char* data, ...) {
	if (!data) return;
	if (!g_default_logger_set) return;

	const auto logger = (Logger *) gv_get_at(&g_loggers, g_default_logger);
	if (!check_if_should_log(log_type, logger->log_level)) {
		return;
	}

	va_list args;
	va_start(args, data);
	logger_log_v(logger, log_type, data, args);
	va_end(args);
}

void set_logger_level_auto(const char log_level) {
	if (g_default_logger_set) {
		set_logger_level(g_default_logger, log_level);
	}
}
