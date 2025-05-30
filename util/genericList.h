//
// Created by Ja on 5/23/2025.
//

#ifndef GENERICLIST_H
#define GENERICLIST_H

#include "utils.h"

typedef struct GenericNode GenericNode;

typedef struct GenericList {
  uint32 elementSize;
  GenericNode *head;
  GenericNode *tail;
  GenericNode *iterator; //iterator breaks after removing elements
} GenericList;

typedef struct GenericNode{
  void* value;
  GenericNode* next;
  GenericNode* prev;
} GenericNode;

void initList(GenericList* list, uint32 elementSize);

void* addNode(GenericList* list);
void deleteLast(GenericList* list);
void deleteFirst(GenericList* list);
void* getFirst(GenericList* list);
void* getLast(GenericList* list);

void* getNext(GenericList* list);
void* getPrev(GenericList* list);
void* current(GenericList* list);
GenericNode* getIterator(GenericList* list);
void resetIterator(GenericList* list);

void deleteAll(GenericList* list);

void printAllData(GenericList* list);

int getListSize(GenericList* list);

//TODO removing at index, inserting in first empty place

#endif //GENERICLIST_H