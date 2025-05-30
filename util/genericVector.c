//
// Created by Ja on 5/30/2025.
//
#include "genericVector.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void gv_init_vector(GenericVector* vector, const uint32 elementSize){
	vector->size = 0;
	vector->capacity = 8;
	vector->element_size = elementSize;
	vector->upper_bound = 2;
	vector->lower_bound = 0.5;
	vector->data = malloc(vector->capacity * vector->element_size);
}

static void increase_capacity(GenericVector* vector) {
	vector->capacity *= 2;
	void* old_data = vector->data;
	vector->data = realloc(vector->data, vector->capacity * vector->element_size);
	if (vector->data == NULL) {
		//old pointer still valid, must be freed to aviod leaking memory
		vector->data = old_data;
		fprintf(stderr, "Out of memory, couldn't reallocate the vector.\n");
	}
}

static void* get_target_ptr(void* start, const uint32 place, const uint32 size) {
	return (char*)start + place * size;
}

void* gv_push_back(GenericVector* vector, const void* value){
	void* target_ptr = get_target_ptr(vector->data, vector->size, vector->element_size);
	memcpy(target_ptr, value, vector->element_size);
	vector->size++;
	if (vector->size == vector->capacity) {
		increase_capacity(vector);
	}
	return target_ptr;
}

void* gv_pop_back(GenericVector* vector){
	vector->size--;
	return gv_get_at(vector, vector->size);
}

void gv_delete_all(GenericVector* vector){
	free(vector->data);
	vector->size = 0;
	vector->capacity = 8;
	vector->data = malloc(vector->capacity * vector->element_size);
}

void* gv_get_at(const GenericVector* vector, const uint32 index){
	return  get_target_ptr(vector->data, index, vector->element_size);
}

void* gv_get_data(const GenericVector* vector) {
	return vector->data;
}

void gv_set_lower_bound(GenericVector* vector, float value){
	vector->lower_bound = value;
}

void gv_set_upper_bound(GenericVector* vector, float value){
	vector->upper_bound = value;
}

void gv_print_all_data(const GenericVector* vector){
	for (int i = 0; i < vector->size; i++) {
		void* value = get_target_ptr(vector->data, i, vector->element_size);
		printf("[");
		printf("%d", *(int*)value);
		printf("]");
		if(i < vector->size - 1) {
			printf(", ");
		}
	}
}
