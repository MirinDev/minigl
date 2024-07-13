#include <math/vec3.h>

vec3_t add_vector_3(vec3_t a, vec3_t b)
{
    vec3_t vec;
    
    vec.x = a.x + b.x;
    vec.y = a.y + b.y;
    vec.z = a.z + b.z;

    return vec;
}

vec3_t subtract_vector_3(vec3_t a, vec3_t b)
{
    vec3_t vec;
    
    vec.x = a.x - b.x;
    vec.y = a.y - b.y;
    vec.z = a.z - b.z;

    return vec;
}

vec3_t multiply_vector_3(vec3_t a, vec3_t b)
{
    vec3_t vec;
    
    vec.x = a.x * b.x;
    vec.y = a.y * b.y;
    vec.z = a.z * b.z;

    return vec;
}

vec3_t divide_vector_3(vec3_t a, vec3_t b)
{
    vec3_t vec;
    
    vec.x = a.x / b.x;
    vec.y = a.y / b.y;
    vec.z = a.z / b.z;

    return vec;
}

vec3_t divide_vector_3_float(vec3_t vector, float scale)
{
    vec3_t v;

    v.x = vector.x / scale;
    v.y = vector.y / scale;
    v.z = vector.z / scale;

    return v;
}


vec3_t cross_vector_3(vec3_t a, vec3_t b)
{
    vec3_t vec;
    
    vec.x = a.y * b.z - a.z * b.y;
    vec.y = a.z * b.x - a.x * b.z;
    vec.z = a.x * b.y - a.y * b.x;

    return vec;
}

vec3_t normalize_vector_3(vec3_t vector)
{
    float lenght = sqrtf(powf(vector.x, 2.0f) + powf(vector.y, 2.0f) + powf(vector.z, 2.0f));
    if (lenght == 0.0f) return vector;

    return divide_vector_3_float(vector, lenght);
}