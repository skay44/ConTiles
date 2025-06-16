//
// Created by Skay44 on 5/24/2025.
//

#ifndef ROW_H
#define ROW_H

#include "variables.h"
#include "genericList.h"

typedef struct Column Column;

typedef struct Row {
	float relative_height;
	uint32 id;
	short rim_style;
	short inside_style;
	GenericList column_list;
} Row;

#endif //ROW_H
