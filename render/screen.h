//
// Created by Ja on 5/23/2025.
//

#ifndef SCREEN_H
#define SCREEN_H

#include "genericList.h"
#include "consoleSwap.h"
#include "column.h"

typedef struct Screen {
	int currentID;
	GenericList generic_list;
	ConsoleSwap swap;
	vec2uint32 prevSize;
} Screen;

void generateView(Screen* screen);
void initializeScreen(Screen* screen);
Column* addColumnToScreen(Screen* screen, float width, short rimStyle, short insideStyle);
Column* addColumnToScreenS(Screen* screen, float width);

#endif //SCREEN_H


