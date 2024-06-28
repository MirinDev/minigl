#ifndef RASTER_H_
#define RASTER_H_

#include "math/vec2.h"
#include "math/vec3.h"
#include "math/vec4.h"
#include "math/mat4.h"

#include <frame.h>

typedef union triangle_3d_u
{
    struct{vec3_t v0, v1, v2;};
    struct{vec3_t data[3];};
} triangle_3d_t;

typedef void fragment_shader(char* ch, float a, float b, float g);

void raster_triangle(frame_t* frame, zframe_t* zframe, triangle_3d_t tri, fragment_shader shader);

#endif