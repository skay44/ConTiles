//
// Created by Ja on 5/23/2025.
//
#ifndef COLUMN_H
#define COLUMN_H

#include "variables.h"
#include "genericList.h"

typedef struct Row Row;

typedef struct Column {
	float relativeWidth;
    uint32 id;
	short rimStyle;
	short insideStyle;
	GenericList row_list;
} Column;

Row* addRowToColumn(Column* column, float height, short rimStyle, short insideStyle);
Row* addRowToColumnS(Column* column, float height);

#endif //COLUMN_H
