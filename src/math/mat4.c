#include <math/mat4.h>

mat4_t identity_matrix_4x4()
{
    mat4_t matrix = (mat4_t)malloc(16 * sizeof(float));
    memset(matrix, 0, 16 * sizeof(float));

    matrix[0] = 1.0f;
    matrix[5] = 1.0f;
    matrix[10] = 1.0f;
    matrix[15] = 1.0f;

    return matrix;
}

mat4_t multiply_matrix_4x4(mat4_t m1, mat4_t m2)
{
    mat4_t m = (mat4_t)malloc(16 * sizeof(float));
    memset(m, 0, 16 * sizeof(float));

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            m[i * 4 + j] = m1[i * 4] * m2[j] + m1[i * 4 + 1] * m2[4 + j] + m1[i * 4 + 2] * m2[8 + j] + m1[i * 4 + 3] * m2[12 + j];

    return m;
}

mat4_t orthographic(float left, float right, float top, float bottom, float near, float far)
{
    mat4_t matrix = (mat4_t)malloc(16 * sizeof(float));
    memset(matrix, 0, 16 * sizeof(float));

    matrix[0] = 1.0 / (right - left);
    matrix[5] = 1.0 / (bottom - top);
    matrix[10] = 1.0 / (far - near);
    matrix[15] = 1.0;

    matrix[3] = -(right + left) / (right - left);
    matrix[7] = -(bottom + top) / (bottom - top);
    matrix[11] = -near / (far - near);

    return matrix;
}

mat4_t perspective(float fov, float aspect, float near, float far)
{
    mat4_t matrix = (mat4_t)malloc(16 * sizeof(float));
    memset(matrix, 0, 16 * sizeof(float));

    float ar = tanf(fov / 2.0f);

    matrix[0] = 1.0 / (aspect * ar);
    matrix[5] = 1.0 / ar;
    matrix[10] = -(far + near) / (far - near);
    matrix[11] = -(2 * far * near) / (far - near);
    matrix[14] = -1.0;

    return matrix;
}

mat4_t look_at(vec3_t pos, vec3_t right, vec3_t up, vec3_t front)
{
    mat4_t matrix = (mat4_t)malloc(16 * sizeof(float));
    memset(matrix, 0, 16 * sizeof(float));

    //

    return matrix;
}

mat4_t translate_matrix_4x4(mat4_t matrix, vec3_t vector)
{
    mat4_t translate_matrix = identity_matrix_4x4();

    translate_matrix[3] = vector.x;
    translate_matrix[7] = vector.y;
    translate_matrix[11] = vector.z;

    return multiply_matrix_4x4(matrix, translate_matrix);
}

mat4_t rotate_matrix_4x4(mat4_t matrix, vec3_t rad)
{
    mat4_t rotate_matrix = identity_matrix_4x4();

    float cx = cosf(rad.x);
    float sx = sinf(rad.x);

    float cy = cosf(rad.y);
    float sy = sinf(rad.y);

    float cz = cosf(rad.z);
    float sz = sinf(rad.z);

    rotate_matrix[0] = cy*cz;
    rotate_matrix[1] = -cy*sz;
    rotate_matrix[2] = sy;

    rotate_matrix[4] = sx*sy*cz + cx*sz;
    rotate_matrix[5] = -sx*sy*sz + cx*cz;
    rotate_matrix[6] = -sx*cy;

    rotate_matrix[8] = -cx*sy*cz + sx*sz;
    rotate_matrix[9] = cx*sy*sz + sx*cz;
    rotate_matrix[10] = cx*cy;

    return multiply_matrix_4x4(matrix, rotate_matrix);
}

mat4_t rotate_with_deg_matrix_4x4(mat4_t matrix, vec3_t deg)
{
    vec3_t rad;
    rad.x = deg_to_rad(deg.x);
    rad.y = deg_to_rad(deg.y);
    rad.z = deg_to_rad(deg.z);

    return rotate_matrix_4x4(matrix, rad);
}

float deg_to_rad(float deg)
{
    return deg * ((float)M_PI / 180.0f);
}

void print_matrix_4x4(mat4_t matrix)
{
    fprintf(stdout, "%.2f, %.2f, %.2f, %.2f\n%.2f, %.2f, %.2f, %.2f\n%.2f, %.2f, %.2f, %.2f\n%.2f, %.2f, %.2f, %.2f\n", 
                    matrix[0], matrix[1], matrix[2], matrix[3],
                    matrix[4], matrix[5], matrix[6], matrix[7],
                    matrix[8], matrix[9], matrix[10], matrix[11],
                    matrix[12], matrix[13], matrix[14], matrix[15]);
}