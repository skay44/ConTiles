//
// Created by Skay44 on 5/23/2025.
//

#ifndef GENERICLIST_H
#define GENERICLIST_H

#include "utils.h"

typedef struct GenericNode GenericNode;

typedef struct GenericList {
	uint32 elementSize;
	GenericNode* head;
	GenericNode* tail;
	GenericNode* iterator; //iterator breaks after removing elements
} GenericList;

typedef struct GenericNode {
	void* value;
	GenericNode* next;
	GenericNode* prev;
} GenericNode;

void init_list(GenericList* list, uint32 elementSize);

void* add_node(GenericList* list);

void delete_last(GenericList* list);

void delete_first(GenericList* list);

void* get_first(GenericList* list);

void* get_last(GenericList* list);

void* get_next(GenericList* list);

void* get_prev(GenericList* list);

void* current(GenericList* list);

GenericNode* get_iterator(GenericList* list);

void reset_iterator(GenericList* list);

void delete_all(GenericList* list);

void print_all_data(GenericList* list);

int get_list_size(GenericList* list);

//TODO removing at index, inserting in first empty place

#endif //GENERICLIST_H
