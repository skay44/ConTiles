//
// Created by Skay44 on 5/23/2025.
//

#ifndef CONSOLESWAP_H
#define CONSOLESWAP_H
#include "variables.h"

typedef struct SkayCharInfo {
	union {
		short unicode_char;
		char ascii;
	} Char;

	short attributes;
} SkayCharInfo;

typedef struct ConsoleSwap {
	SkayCharInfo* buffer;
	vec2uint32 size;
} ConsoleSwap;

void set_swap_size(ConsoleSwap* swap, vec2uint32 size);

void init_swap(ConsoleSwap* swap);

#endif //CONSOLESWAP_H
