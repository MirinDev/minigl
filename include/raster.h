#ifndef RASTER_H_
#define RASTER_H_

#include "math/vec2.h"
#include "math/vec3.h"

#include <frame.h>

typedef union triangle_2d_u
{
    struct{vec2i_t v0, v1, v2;};
    struct{vec2i_t data[3];};
} triangle_2d_t;

typedef union triangle_3d_u
{
    struct{vec3_t v0, v1, v2;};
    struct{vec3_t data[3];};
} triangle_3d_t;

void raster_triangle(frame_t* frame_t, triangle_2d_t tri);

#endif