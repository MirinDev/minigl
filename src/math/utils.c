#include <math/utils.h>

float minf(float a, float b)
{
    return a < b ? a : b;
}

float maxf(float a, float b)
{
    return a > b ? a : b;
}

float clampf(float a, float b, float c)
{
    return a < b ? b : a > c ? c : a;
}

float absf(float a)
{
    return a < 0.0f ? -a : a;
}
