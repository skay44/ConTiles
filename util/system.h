//
// Created by Skay44 on 5/23/2025.
//

#ifndef SYSTEM_H
#define SYSTEM_H

#include "variables.h"
#include "const.h"
#include "consoleSwap.h"

typedef enum OS {
	windows,
	linux,
	android,
	unknown
} OS;

OS getOS();

vec2uint32 get_screen_size();

void clear_screen();

void write_char(char c, vec2uint32 position);

void init_console();

void write_buffer_on_screen_buffer(ConsoleSwap* swap);


#endif //SYSTEM_H
