//
// Created by Ja on 5/23/2025.
//
#include "consoleSwap.h"
#include <stdlib.h>

void setSwapSize(ConsoleSwap* swap, vec2uint32 size){
  swap->size = size;
  free(swap->buffer);
  swap->buffer = malloc(size.x * size.y * sizeof(SkayCharInfo));
}

void initializeSwap(ConsoleSwap* swap){
  swap->buffer = NULL;
  vec2uint32 size = {0,0};
  swap->size = size;
}