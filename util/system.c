//
// Created by Skay44 on 5/23/2025.
//

#include "system.h"
#include <stdio.h>

OS getOS() {
	if (PLATFORM_NAME == "windows") {
		return windows;
	} else if (PLATFORM_NAME == "linux") {
		return linux;
	} else if (PLATFORM_NAME == "android") {
		return android;
	} else {
		return unknown;
	}
}

#ifdef USING_WINDOWS

void init_console() {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dw_mode = 0;
	GetConsoleMode(hOut, &dw_mode);
	dw_mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOut, dw_mode);
}

vec2uint32 get_screen_size() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	int rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	vec2uint32 size = {columns, rows};

	return size;
}

void clear_screen() {
	system("cls");
}

void write_char(char c, vec2uint32 position) {
	printf("\033[%d;%dHA", position.y, position.x);
}

void write_buffer_on_screen_buffer(ConsoleSwap* swap) {
	//  char a[swap->size.x*swap->size.y];
	//  for(int i = 0; i < swap->size.x*swap->size.y; i++){
	//    a[i] = swap->buffer[i].Char.ascii;
	//  }
	//
	//  fwrite(a,1, swap->size.x*swap->size.y, stdout);

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOut == INVALID_HANDLE_VALUE) return;

	SMALL_RECT region = {0, 0, swap->size.x - 1, swap->size.y - 1};
	COORD size = {swap->size.x, swap->size.y};
	COORD position = {0, 0};

	WriteConsoleOutput(hOut, (CHAR_INFO *) swap->buffer, size, position, &region);
}

#elifdef USING_LINUX

void init_console(){
  //nothing to do here
}


vec2uint32 get_screen_size(){
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

  vec2uint32 size = { w.ws_col, w.ws_row };
  return size;
}

void clear_screen(){
  system("clear");
}

void write_char(char c, vec2uint32 position){
  printf("A");
}

void write_buffer_on_screen_buffer(ConsoleSwap* swap){
  write(STDOUT_FILENO, swap->buffer, getScreenSize().x*getScreenSize().y);
  WriteConsoleOutput()
}

#elifdef USING_ANDROID

vec2uint getScreenSize(){
  //NOT IMPLEMENTED
}

#else

vec2uint getScreenSize(){
  //NOT IMPLEMENTED
}

#endif
