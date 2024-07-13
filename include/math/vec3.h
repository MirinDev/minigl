#ifndef VEC3_H_
#define VEC3_H_

#include <math.h>

typedef struct vec3_s
{
    float x, y, z;
} vec3_t;

vec3_t add_vector_3(vec3_t a, vec3_t b);

vec3_t subtract_vector_3(vec3_t a, vec3_t b);

vec3_t multiply_vector_3(vec3_t a, vec3_t b);

vec3_t divide_vector_3(vec3_t a, vec3_t b);

vec3_t divide_vector_3_float(vec3_t vector, float scale);

vec3_t cross_vector_3(vec3_t a, vec3_t b);

vec3_t normalize_vector_3(vec3_t vector);

#endif