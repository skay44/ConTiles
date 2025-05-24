//
// Created by Ja on 5/24/2025.
//

#ifndef ROW_H
#define ROW_H

#include "variables.h"
#include "genericList.h"

typedef struct Column Column;

typedef struct Row {
	float relativeHeight;
	uint32 id;
	short rimStyle;
	short insideStyle;
	GenericList column_list;
} Row;

#endif //ROW_H
