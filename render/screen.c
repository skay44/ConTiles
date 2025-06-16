//
// Created by Skay44 on 5/23/2025.
//

#include "screen.h"
#include <logger.h>
#include "column.h"
#include "genericList.h"

#include "consoleSwap.h"
#include "row.h"
#include <stdio.h>
#include "system.h"

short const RAINBOW_ANSI_SIZE = 6;
short const RainbowANSI[] =
{
	FOREGROUND_RED,
	FOREGROUND_RED | FOREGROUND_GREEN,
	FOREGROUND_GREEN,
	FOREGROUND_GREEN | FOREGROUND_BLUE,
	FOREGROUND_BLUE,
	FOREGROUND_BLUE | FOREGROUND_RED,
};

short const GRAYSCALE_ANSI_SIZE = 2;
short const GrayscaleANSI[] =
{
	FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
};

short get_rainbow_attributes(int i) {
	return RainbowANSI[i % RAINBOW_ANSI_SIZE];
}

short get_grayscale_get_attributes(int i) {
	return GrayscaleANSI[i % GRAYSCALE_ANSI_SIZE];
}

void get_clean_bufer(Screen* screen, const vec2uint32 scr_size) {
	//TODO remove it
	//its temporary to make debugging easier - black screen means default unchanged buffer
	for (int y = 0; y < scr_size.y; y++) {
		for (int x = 0; x < scr_size.x; x++) {
			screen->swap.buffer[(y) * scr_size.x + x].Char.ascii = ' ';
			screen->swap.buffer[(y) * scr_size.x + x].attributes = 0;
		}
	}
}

void calculate_row_height(Row* rows[], int height[], const int list_size, const vec2uint32 scr_size) {
	float totalHeight = 0;
	for (int i = 0; i < list_size; i++) {
		totalHeight += rows[i]->relative_height;
	}
	height[0] = 0;
	bool roundedDown = false;
	for (int i = 1; i <= list_size; i++) {
		const float exactValue = rows[i - 1]->relative_height / totalHeight * (float) scr_size.y;
		if (!roundedDown) {
			height[i] = (int) exactValue + height[i - 1];
			if (height[i] < (int) exactValue) {
				roundedDown = true;
			}
		} else {
			height[i] = (int) exactValue + 1 + height[i - 1];
			roundedDown = false;
		}
		logger_log_auto(DEBUG, "calculating row height: %d", 125);
	}
	height[list_size] = scr_size.y;
}

void calculate_column_width(Column* columns[], int width[], const int list_size, const vec2uint32 scr_size) {
	float total_width = 0;
	for (int i = 0; i < list_size; i++) {
		total_width += columns[i]->relative_width;
	}
	width[0] = 0;
	bool rounded_down = false;
	for (int i = 1; i <= list_size; i++) {
		const float exact_value = columns[i - 1]->relative_width / total_width * (float) scr_size.x;
		if (!rounded_down) {
			width[i] = (int) exact_value + width[i - 1];
			if (width[i] < exact_value) {
				rounded_down = true;
			}
		} else {
			width[i] = (int) exact_value + 1 + width[i - 1];
			rounded_down = false;
		}
	}
	width[list_size] = scr_size.x;
}

void generate_row(Screen* screen, Row* row, int start, int end, const vec2uint32 screen_start,
                  const vec2uint32 screen_end) {
	if (end > screen_end.x) end = screen_end.x;
	for (int y = screen_start.y + start; y < screen_start.y + end; y++) {
		for (int x = screen_start.x; x < screen_end.x; x++) {
			if (x == screen_start.x || x == screen_end.x - 1 || y == screen_start.y + start || y == screen_start.y + end
			    - 1) {
				screen->swap.buffer[(y) * screen_end.x + x].Char.ascii = '#';
				screen->swap.buffer[(y) * screen_end.x + x].attributes = row->rim_style;
			} else {
				screen->swap.buffer[(y) * screen_end.x + x].attributes = row->inside_style;
			}
		}
	}
}

void generate_column(Screen* screen, Column* column, int start, int end, const vec2uint32 scr_start,
                     const vec2uint32 scr_end) {
	const int row_amount = get_list_size(&column->row_list);
	if (row_amount == 0) {
		if (end > scr_end.x) end = scr_end.x;
		for (int y = scr_start.y; y < scr_end.y; y++) {
			for (int x = scr_start.x + start; x < scr_start.x + end; x++) {
				if (x == scr_start.x + start || x == scr_start.x + end - 1 || y == scr_end.y - 1 || y == scr_start.y) {
					screen->swap.buffer[(y) * scr_end.x + x].Char.ascii = '#';
					screen->swap.buffer[(y) * scr_end.x + x].attributes = column->rim_style;
				} else {
					screen->swap.buffer[(y) * scr_end.x + x].attributes = column->inside_style;
				}
			}
		}
	} else {
		GenericList* row_list = &column->row_list;
		reset_iterator(row_list);
		Row* rows[row_amount];
		int heights[row_amount + 1];

		int i = 0;
		while (current(row_list) != NULL) {
			rows[i++] = get_next(row_list);
		}

		const vec2uint32 scr_new_start = {start, scr_start.y};
		const vec2uint32 screen_end = {end, scr_end.y};
		const vec2uint32 scr_size = {end - start, scr_end.y - scr_start.y};

		calculate_row_height(rows, heights, row_amount, scr_size);

		for (int j = 0; j < row_amount; j++) {
			generate_row(screen, rows[j], heights[j], heights[j + 1], scr_new_start, screen_end);
		}
	}
}

void generate_buffer(Screen* screen, Column* columns[], int width[], const int list_size, const vec2uint32 scr_size) {
	for (int i = 0; i < list_size; i++) {
		vec2uint32 scr_start = {0, 0};
		generate_column(screen, columns[i], width[i], width[i + 1], scr_start, scr_size);
	}
}


void update_view(Screen* screen) {
	GenericList* col_list = &screen->generic_list;
	int list_size = get_list_size(col_list);

	Column* columns[list_size];
	int width[list_size + 1];

	reset_iterator(col_list);
	int i = 0;
	while (current(col_list) != NULL) {
		columns[i++] = get_next(col_list);
	}

	set_swap_size(&screen->swap, get_screen_size());
	vec2uint32 scr_size = screen->swap.size;
	screen->prev_size = scr_size;
	if (scr_size.x < 0) scr_size.x = 0;
	if (scr_size.y < 0) scr_size.y = 0;
	if (scr_size.x > 2000) scr_size.x = 1; //TODO temporary
	if (scr_size.y > 2000) scr_size.y = 1;

	calculate_column_width(columns, width, list_size, scr_size);

	get_clean_bufer(screen, scr_size);
	generate_buffer(screen, columns, width, list_size, scr_size);

	//clearScreen();
	write_buffer_on_screen_buffer(&screen->swap);
	fflush(stdout);
}

void generate_view(Screen* screen) {
	bool to_update = false;
	vec2uint32 scr_size = get_screen_size();
	if (screen->prev_size.x != scr_size.x || screen->prev_size.y != scr_size.y) {
		to_update = true;
		if (screen->prev_size.x * screen->prev_size.y > scr_size.x * scr_size.y) {
			clear_screen();
		}
	}
	if (to_update) update_view(screen);
}

void initialize_screen(Screen* screen) {
	screen->current_id = 0;
	init_console();
	init_list(&screen->generic_list, sizeof(Column));
	init_swap(&screen->swap);
	set_swap_size(&screen->swap, get_screen_size());
}

Column* add_column_to_screen(Screen* screen, float width, short rim_style, short inside_style) {
	Column* column = add_node(&screen->generic_list);
	column->relative_width = width;
	column->rim_style = rim_style;
	column->inside_style = inside_style;
	column->id = screen->current_id++;
	init_list(&column->row_list, sizeof(Row));

	return column;
}

Column* add_column_to_screen_s(Screen* screen, float width) {
	return add_column_to_screen(screen, width, 1, 1);
}
