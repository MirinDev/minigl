#ifndef RENDER_H_
#define RENDER_H_

#include <raster.h>

typedef struct poly_s
{
    triangle_3d_t* data;
    int n;
} poly_t;

typedef void vertex_shader(vec3_t* vert);

void render_poly(frame_t* frame, poly_t* poly, vertex_shader shader);

#endif