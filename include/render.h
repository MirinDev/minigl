#ifndef RENDER_H_
#define RENDER_H_

#include <raster.h>

typedef struct poly_s
{
    vec3_t* data;
    unsigned int* inds;
    unsigned int n;
} poly_t;

typedef void vertex_shader(vec4_t* vert, int i, int j);

void render_poly(frame_t* frame, poly_t* poly, vertex_shader v_shader, fragment_shader f_shader);

#endif