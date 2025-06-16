//
// Created by Skay44 on 5/24/2025.
//

#include "column.h"
#include "genericList.h"
#include "row.h"

Row* add_row_to_column(Column* column, const float height, const short rim_style, const short inside_style) {
	Row* row = add_node(&column->row_list);
	row->relative_height = height;
	row->rim_style = rim_style;
	row->inside_style = inside_style;
	init_list(&row->column_list, sizeof(Column));
	return row;
}

Row* add_row_to_column_s(Column* column, const float height) {
	return add_row_to_column(column, height, 1, 1);
}
