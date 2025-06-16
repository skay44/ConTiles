//
// Created by Skay44 on 5/23/2025.
//

#ifndef COLUMN_H
#define COLUMN_H

#include "variables.h"
#include "genericList.h"

typedef struct Row Row;

typedef struct Column {
	float relative_width;
	uint32 id;
	short rim_style;
	short inside_style;
	GenericList row_list;
} Column;

Row* add_row_to_column(Column* column, float height, short rim_style, short inside_style);

Row* add_row_to_column_s(Column* column, float height);

#endif //COLUMN_H
