#include <math/vec4.h>

vec4_t normalize_vector_4(vec4_t vector)
{
    float lenght = sqrtf(powf(vector.x, 2.0f) + powf(vector.y, 2.0f) + powf(vector.z, 2.0f) + powf(vector.w, 2.0f));
    if (lenght == 0.0f) return vector;

    return divide_vector_4(vector, lenght);
}

vec4_t divide_vector_4(vec4_t vector, float scale)
{
    vec4_t v;

    v.x = vector.x / scale;
    v.y = vector.y / scale;
    v.z = vector.z / scale;
    v.w = vector.w / scale;

    return v;
}

vec4_t vec3_to_vec4(vec3_t vector, float scale)
{
    vec4_t v;

    v.x = vector.x;
    v.y = vector.y;
    v.z = vector.z;
    v.w = scale;
    
    return v;
}

vec4_t multiply_matrix_4x4_vector4(mat4_t matrix, vec4_t vector)
{
    vec4_t v;

    v.x = vector.x * matrix[0] + vector.y * matrix[1] + vector.z * matrix[2] + vector.w * matrix[3];
    v.y = vector.x * matrix[4] + vector.y * matrix[5] + vector.z * matrix[6] + vector.w * matrix[7];
    v.z = vector.x * matrix[8] + vector.y * matrix[9] + vector.z * matrix[10] + vector.w * matrix[11];
    v.w = vector.x * matrix[12] + vector.y * matrix[13] + vector.z * matrix[14] + vector.w * matrix[15];

    return v;
}