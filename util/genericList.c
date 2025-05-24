//
// Created by Ja on 5/23/2025.
//
#include "genericList.h"
#include <stdlib.h>

#include <stdio.h>

void initList(GenericList* list, uint32 elementSize) {
  list->head = NULL;
  list->tail = NULL;
  list->iterator = NULL;
  list->elementSize = elementSize;
}

void* addNode(GenericList* list){
  GenericNode* node = (GenericNode*)malloc(sizeof(GenericNode));
  void* data = malloc(list->elementSize);

  node->value = data;
  node->next = NULL;
  node->prev = NULL;

  if(list->head == NULL){
    list->head = node;
    list->tail = node;
    list->iterator = node;
  }
  else{
    list->tail->next = node;
    node->prev = list->tail;
    list->tail = node;
  }
  return data;
}

void deleteLast(GenericList* list){
  if(list->head == NULL){
    return;
  }

  GenericNode* last = list->tail;
  void* data = last->value;

  if(last->prev != NULL){
    list->tail = last->prev;
    list->tail->next = NULL;
  } else {
    list->head = NULL;
    list->tail = NULL;
  }

  free(last);
  free(data);
}

void deleteFirst(GenericList* list){
  if(list->head == NULL){
    return;
  }

  GenericNode* first = list->head;
  void* data = first->value;

  if(first->next != NULL){
    list->head = first->next;
    list->head->prev = NULL;
  } else {
    list->head = NULL;
    list->tail = NULL;
  }

  free(first);
  free(data);
}

void* getFirst(GenericList* list){
  return list->head->value;
}

void* getLast(GenericList* list){
  return list->tail->value;
}

void* getNext(GenericList* list){
  if(list->iterator == NULL){
    return NULL;
  }
  void* toReturn = list->iterator->value;
  list->iterator = list->iterator->next;
  return toReturn;
}

void* current(GenericList* list){
  if(list->iterator == NULL){
    return NULL;
  }
  return list->iterator->value;
}

GenericNode* getIterator(GenericList* list){
  return list->iterator;
}

void resetIterator(GenericList* list){
  list->iterator = list->head;
}

void deleteAll(GenericList* list){
  if(list->head == NULL){
    return;
  }

  while(list->tail != NULL){
    GenericNode* last = list->tail;
    void* data = last->value;

    list->tail = last->prev;

    free(last);
    free(data);
  }
  list->head = NULL;
  list->iterator = NULL;
}

void printAllData(GenericList* list){
  if(list->head == NULL){
    return;
  }

  GenericNode* node = list->head;
  while(node != NULL){
    GenericNode* next = node->next;
    void* data = node->value;
    printf("[");
    printf("%d", *(int*)data);
    printf("]");
    if(next != NULL){
      printf(", ");
    }
    node = node->next;
  }
}

int getListSize(GenericList* list){
  int listSize = 0;
  resetIterator(list);
  while(current(list) != NULL){
    void* value = getNext(list);
    if(value == NULL) break;
    listSize++;
  }
  return listSize;
}