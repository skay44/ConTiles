//
// Created by Skay44 on 5/23/2025.
//

#ifndef SCREEN_H
#define SCREEN_H

#include "genericList.h"
#include "consoleSwap.h"
#include "column.h"

extern short const RAINBOW_ANSI_SIZE;
extern short const RainbowANSI[];

extern short const GRAYSCALE_ANSI_SIZE;
extern short const GrayscaleANSI[];

typedef struct Screen {
	int current_id;
	GenericList generic_list;
	ConsoleSwap swap;
	vec2uint32 prev_size;
} Screen;

void generate_view(Screen* screen);

void initialize_screen(Screen* screen);

Column* add_column_to_screen(Screen* screen, float width, short rim_style, short inside_style);

Column* add_column_to_screen_s(Screen* screen, float width);

#endif //SCREEN_H
