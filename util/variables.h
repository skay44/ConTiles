//
// Created by Skay44 on 5/23/2025.
//

#ifndef VARIABLES_HPP
#define VARIABLES_HPP

#include <stdint.h>

//single

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;
typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;


//vec2

typedef struct vec2int {
	int x, y;
} vec2int;

typedef struct uvec2int {
	unsigned int x, y;
} vec2uint;

typedef struct vec2uint8 {
	uint8 x, y;
} vec2uint8;

typedef struct vec2uint16 {
	uint16 x, y;
} vec2uint16;

typedef struct vec2uint32 {
	uint32 x, y;
} vec2uint32;

typedef struct vec2uint64 {
	uint64 x, y;
} vec2uint64;

typedef struct vec2int8 {
	int8 x, y;
} vec2int8;

typedef struct vec2int16 {
	int16 x, y;
} vec2int16;

typedef struct vec2int32 {
	int32 x, y;
} vec2int32;

typedef struct vec2int64 {
	int64 x, y;
} vec2int64;

//vec3

typedef struct vec32int {
	int x, y, z;
} vec3int;

typedef struct uvec3int {
	unsigned int x, y, z;
} vec3uint;

typedef struct vec3uint8 {
	uint8 x, y, z;
} vec3uint8;

typedef struct vec3uint16 {
	uint16 x, y, z;
} vec3uint16;

typedef struct vec3uint32 {
	uint32 x, y, z;
} vec3uint32;

typedef struct vec3uint64 {
	uint64 x, y, z;
} vec3uint64;

typedef struct vec3int8 {
	int8 x, y, z;
} vec3int8;

typedef struct vec3int16 {
	int16 x, y, z;
} vec3int16;

typedef struct vec3int32 {
	int32 x, y, z;
} vec3int32;

typedef struct vec3int64 {
	int64 x, y, z;
} vec3int64;

#endif //VARIABLES_HPP
