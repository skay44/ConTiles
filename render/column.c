//
// Created by Ja on 5/24/2025.
//
#include "column.h"
#include "genericList.h"
#include "row.h"

Row* addRowToColumn(Column* column, float height, short rimStyle, short insideStyle){
	Row* row = addNode(&column->row_list);
	row->relativeHeight = height;
	row->rimStyle = rimStyle;
	row->insideStyle = insideStyle;
	initList(&row->column_list, sizeof(Column));

	return row;
}

Row* addRowToColumnS(Column* column, float height){
	return addRowToColumn(column, height, 1,1);
}