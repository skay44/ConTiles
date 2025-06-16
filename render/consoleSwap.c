//
// Created by Skay44 on 5/23/2025.
//

#include "consoleSwap.h"
#include <stdlib.h>

void set_swap_size(ConsoleSwap* swap, const vec2uint32 size) {
	swap->size = size;
	free(swap->buffer);
	swap->buffer = malloc(size.x * size.y * sizeof(SkayCharInfo));
}

void init_swap(ConsoleSwap* swap) {
	swap->buffer = NULL;
	const vec2uint32 size = {0, 0};
	swap->size = size;
}
