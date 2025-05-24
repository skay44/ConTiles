//
// Created by Ja on 5/23/2025.
//

#include "screen.h"
#include "column.h"
#include "genericList.h"
#include "system.h"
#include "consoleSwap.h"
#include "row.h"
#include <stdio.h>

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

short getRainbowAttributes(int i){
  return RainbowANSI[i % RAINBOW_ANSI_SIZE];
}

short getGrayscaleAttributes(int i){
	return GrayscaleANSI[i % GRAYSCALE_ANSI_SIZE];
}

void getCleanBufer(Screen* screen,vec2uint32 scrSize){ //TODO temporary
	for(int y = 0; y < scrSize.y; y++){
		for(int x = 0; x < scrSize.x; x++){
			screen->swap.buffer[(y)*scrSize.x+x].Char.ascii = ' ';
			screen->swap.buffer[(y)*scrSize.x+x].attributes = 0;
        }
    }
}

void calculateRowHeight(Row* rows[], int height[],int listSize,vec2uint32 scrSize){
	float totalHeight = 0;
	for(int i = 0; i < listSize; i++){
		totalHeight += rows[i]->relativeHeight;
	}
	height[0] = 0;
	bool roundedDown = false;
	for(int i = 1; i <= listSize; i++){
		float exactValue = ((float)(rows[i - 1]->relativeHeight) / totalHeight * scrSize.y);
		if(!roundedDown){
			height[i] = (int)exactValue + height[i - 1];
			if(height[i] < exactValue){
				roundedDown = true;
			}
		}
		else{
			height[i] = (int)exactValue+1 + height[i - 1];
			roundedDown = false;
		}
	}
	height[listSize] = scrSize.y;
}

void calculateColumnWidth(Column* columns[], int width[],int listSize,vec2uint32 scrSize){
	float totalWidth = 0;
	for(int i = 0; i < listSize; i++){
		totalWidth += columns[i]->relativeWidth;
	}
	width[0] = 0;
	bool roundedDown = false;
	for(int i = 1; i <= listSize; i++){
		float exactValue = ((float)(columns[i - 1]->relativeWidth) / totalWidth * scrSize.x);
		if(!roundedDown){
			width[i] = (int)exactValue + width[i - 1];
			if(width[i] < exactValue){
				roundedDown = true;
			}
		}
		else{
			width[i] = (int)exactValue+1 + width[i - 1];
			roundedDown = false;
		}
	}
	width[listSize] = scrSize.x;
}

void generateRow(Screen* screen, Row* row, int start, int end,vec2uint32 scrStart, vec2uint32 scrEnd){
	if(end > scrEnd.x) end = scrEnd.x;
	for(int y = scrStart.y + start; y < scrStart.y + end; y++){
		for(int x = scrStart.x; x < scrEnd.x; x++){
			if(x == scrStart.x || x == scrEnd.x-1 || y == scrStart.y + start || y == scrStart.y + end -1){
				screen->swap.buffer[(y)*scrEnd.x+x].Char.ascii = '#';
				screen->swap.buffer[(y)*scrEnd.x+x].attributes = row->rimStyle;
			}
			else{
				screen->swap.buffer[(y)*scrEnd.x+x].attributes = row->insideStyle;
			}
		}
	}
}

void generateColumn(Screen* screen, Column* column, int start, int end,vec2uint32 scrStart,vec2uint32 scrEnd){
  	int rowAmount = getListSize(&column->row_list);
    if(rowAmount == 0){
    	if(end > scrEnd.x) end = scrEnd.x;
    	for(int y = scrStart.y; y < scrEnd.y; y++){
    		for(int x = scrStart.x + start; x < scrStart.x + end; x++){
    			if(x == scrStart.x + start || x == scrStart.x + end-1 || y == scrEnd.y-1 || y == scrStart.y){
    				screen->swap.buffer[(y)*scrEnd.x+x].Char.ascii = '#';
    				screen->swap.buffer[(y)*scrEnd.x+x].attributes = column->rimStyle;
    			}
    			else{
    				screen->swap.buffer[(y)*scrEnd.x+x].attributes = column->insideStyle;
    			}
    		}
    	}
    }
    else{
        GenericList* row_list = &column->row_list;
    	resetIterator(row_list);
        Row* rows[rowAmount];
        int heights[rowAmount+1];

    	int i = 0;
    	while(current(row_list) != NULL){
    		rows[i++] = getNext(row_list);
    	}

    	vec2uint32 scrNewStart = {start, scrStart.y};
        vec2uint32 scrNewEnd = {end, scrEnd.y};
    	vec2uint32 newSize = {end - start, scrEnd.y - scrStart.y};

    	calculateRowHeight(rows, heights,rowAmount,newSize);

        for(int i = 0; i < rowAmount; i++){
        	generateRow(screen,rows[i],heights[i],heights[i+1],scrNewStart,scrNewEnd);
        }

    }
}

void generateBuffer(Screen* screen, Column* columns[], int width[],int listSize,vec2uint32 scrSize){
	for(int i = 0; i < listSize; i++){
        vec2uint32 scrStart = {0,0};
		generateColumn(screen, columns[i], width[i], width[i+1], scrStart, scrSize);
	}
}



void updateView(Screen* screen){

	GenericList* col_list = &screen->generic_list;
    int listSize = getListSize(col_list);

    Column* columns[listSize];
    int width[listSize+1];

	resetIterator(col_list);
    int i = 0;
	while(current(col_list) != NULL){
		columns[i++] = getNext(col_list);
	}

	setSwapSize(&screen->swap, getScreenSize());
	vec2uint32 scrSize = screen->swap.size;
	screen->prevSize = scrSize;
    if(scrSize.x < 0) scrSize.x = 0;
    if(scrSize.y < 0) scrSize.y = 0;
    if(scrSize.x > 2000) scrSize.x = 2000;//TODO temporary
    if(scrSize.y > 2000) scrSize.y = 2000;

	calculateColumnWidth(columns,width,listSize,scrSize);

	getCleanBufer(screen,scrSize);
	generateBuffer(screen,columns,width,listSize,scrSize);

	//clearScreen();
    write_buffer_on_screen_buffer(&screen->swap);
	fflush(stdout);
}

void generateView(Screen* screen){
  	bool toUpdate = false;
	vec2uint32 scrSize = getScreenSize();
  	if(screen->prevSize.x != scrSize.x || screen->prevSize.y != scrSize.y){
		toUpdate = true;
  		if (screen->prevSize.x * screen->prevSize.y > scrSize.x * scrSize.y) {
  			clearScreen();
  		}
  	}
    if(toUpdate) updateView(screen);
}

void initializeScreen(Screen* screen){
  	screen->currentID = 0;
	initConsole();
  	initList(&screen->generic_list, sizeof(Column));
    initializeSwap(&screen->swap);
    setSwapSize(&screen->swap, getScreenSize());
}

Column* addColumnToScreen(Screen* screen, float width, short rimStyle, short insideStyle){
	Column* column = addNode(&screen->generic_list);
	column->relativeWidth = width;
    column->rimStyle = rimStyle;
    column->insideStyle = insideStyle;
    column->id = screen->currentID++;
	initList(&column->row_list, sizeof(Row));

    return column;
}

Column* addColumnToScreenS(Screen* screen, float width){
  return addColumnToScreen(screen, width, 1,1);
}