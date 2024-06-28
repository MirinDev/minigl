#ifndef VEC4_H_
#define VEC4_H_

#include <math.h>

#include "vec3.h"
#include "mat4.h"

typedef struct vec4_s
{
    float x, y, z, w;
} vec4_t;

vec4_t normalize_vector_4(vec4_t vector);
vec4_t divide_vector_4(vec4_t vector, float scale);
vec4_t multiply_matrix_4x4_vector4(mat4_t matrix, vec4_t vector);
vec4_t vec3_to_vec4(vec3_t vector, float scale);

#endif