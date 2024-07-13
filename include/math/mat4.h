#ifndef MAT4_H_
#define MAT4_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vec3.h"
#include "utils.h"

typedef struct mat4_s 
{
    float data[16];
} mat4_t;

mat4_t identity_matrix_4x4();
mat4_t multiply_matrix_4x4(mat4_t m1, mat4_t m2);
mat4_t create_transform_matrix_4x4(vec3_t translate, vec3_t rotate, vec3_t scale);

mat4_t create_orthographic_matrix_4x4(float left, float right, float top, float bottom, float near, float far);
mat4_t create_perspective_matrix_4x4(float fov, float aspect, float near, float far);
mat4_t create_look_at_matrix_4x4(vec3_t eye, vec3_t target, vec3_t up);

mat4_t translate_matrix_4x4(mat4_t matrix, vec3_t vector);
mat4_t scale_matrix_4x4(mat4_t matrix, vec3_t vector);
mat4_t rotate_matrix_4x4(mat4_t matrix, vec3_t rad);

void print_matrix_4x4(mat4_t matrix);

#endif