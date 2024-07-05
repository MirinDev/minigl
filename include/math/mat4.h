#ifndef MAT4_H_
#define MAT4_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "vec3.h"

typedef struct mat4_s 
{
    float data[16];
} mat4_t;

mat4_t identity_matrix_4x4();
mat4_t multiply_matrix_4x4(mat4_t m1, mat4_t m2);

mat4_t orthographic(float left, float right, float top, float bottom, float near, float far);
mat4_t perspective(float fov, float aspect, float near, float far);
mat4_t look_at(vec3_t pos, vec3_t right, vec3_t up, vec3_t front);

mat4_t translate_matrix_4x4(mat4_t matrix, vec3_t vector);
mat4_t scale_matrix_4x4(mat4_t matrix, vec3_t vector);
mat4_t rotate_matrix_4x4(mat4_t matrix, vec3_t rad);
mat4_t rotate_with_deg_matrix_4x4(mat4_t matrix, vec3_t deg);


float deg_to_rad(float deg);

void print_matrix_4x4(mat4_t matrix);

#endif