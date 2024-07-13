#include <math/mat4.h>

mat4_t identity_matrix_4x4()
{
    mat4_t matrix = {0.0f};

    matrix.data[0] = 1.0f;
    matrix.data[5] = 1.0f;
    matrix.data[10] = 1.0f;
    matrix.data[15] = 1.0f;

    return matrix;
}

mat4_t multiply_matrix_4x4(mat4_t m1, mat4_t m2)
{
    mat4_t m;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            m.data[i * 4 + j] = m1.data[i * 4] * m2.data[j] + m1.data[i * 4 + 1] * m2.data[4 + j] + m1.data[i * 4 + 2] * m2.data[8 + j] + m1.data[i * 4 + 3] * m2.data[12 + j];
    
    return m;
}

mat4_t orthographic(float left, float right, float top, float bottom, float near, float far)
{
    mat4_t matrix = {0.0f};

    matrix.data[0] = 2.0f / (right - left);
    matrix.data[5] = 2.0f / (top - bottom);
    matrix.data[10] = -2.0f / (far - near);
    matrix.data[15] = 1.0f;

    matrix.data[3] = -(right + left) / (right - left);
    matrix.data[7] = -(top + bottom) / (top - bottom);
    matrix.data[11] = -(far + near) / (far - near);

    return matrix;
}

mat4_t perspective(float fov, float aspect, float near, float far)
{
    mat4_t matrix = {0.0f};

    float ar = tanf(fov / 2.0f);

    matrix.data[0] = 1.0f / (aspect * ar);
    matrix.data[5] = 1.0f / ar;
    matrix.data[10] = -(far + near) / (far - near);
    matrix.data[11] = -(2.0f * far * near) / (far - near);
    matrix.data[14] = -1.0f;

    return matrix;
}

mat4_t look_at(vec3_t pos, vec3_t right, vec3_t up, vec3_t front)
{
    mat4_t matrix = {0.0f};

    return matrix;
}

mat4_t translate_matrix_4x4(mat4_t matrix, vec3_t vector)
{
    mat4_t translate_matrix = identity_matrix_4x4();

    translate_matrix.data[3] = vector.x;
    translate_matrix.data[7] = vector.y;
    translate_matrix.data[11] = vector.z;

    return multiply_matrix_4x4(matrix, translate_matrix);
}

mat4_t scale_matrix_4x4(mat4_t matrix, vec3_t vector)
{
    mat4_t scale_matrix = identity_matrix_4x4();

    scale_matrix.data[0] = vector.x;
    scale_matrix.data[5] = vector.y;
    scale_matrix.data[10] = vector.z;

    return multiply_matrix_4x4(matrix, scale_matrix);
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

    rotate_matrix.data[0] = cy*cz;
    rotate_matrix.data[1] = -cy*sz;
    rotate_matrix.data[2] = sy;

    rotate_matrix.data[4] = sx*sy*cz + cx*sz;
    rotate_matrix.data[5] = -sx*sy*sz + cx*cz;
    rotate_matrix.data[6] = -sx*cy;

    rotate_matrix.data[8] = -cx*sy*cz + sx*sz;
    rotate_matrix.data[9] = cx*sy*sz + sx*cz;
    rotate_matrix.data[10] = cx*cy;

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
                    matrix.data[0], matrix.data[1], matrix.data[2], matrix.data[3],
                    matrix.data[4], matrix.data[5], matrix.data[6], matrix.data[7],
                    matrix.data[8], matrix.data[9], matrix.data[10], matrix.data[11],
                    matrix.data[12], matrix.data[13], matrix.data[14], matrix.data[15]);
}