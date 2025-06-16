//
// Created by Skay44 on 5/30/2025.
//

#ifndef GENERICVECTOR_H
#define GENERICVECTOR_H

#include "utils.h"

typedef struct GenericVector {
	uint32 size;
	uint32 capacity;
	uint32 element_size;
	float lower_bound;
	float upper_bound;
	int* data;
} GenericVector;

void gv_init_vector(GenericVector* vector, uint32 element_size);

void* gv_push_back(GenericVector* vector, const void* value);

void* gv_pop_back(GenericVector* vector);

void gv_delete_all(GenericVector* vector);

void* gv_get_at(const GenericVector* vector, uint32 index);

void* gv_get_data(const GenericVector* vector);

void gv_set_lower_bound(GenericVector* vector, float value);

void gv_set_upper_bound(GenericVector* vector, float value);

void gv_print_all_data(const GenericVector* vector);


#endif //GENERICVECTOR_H
