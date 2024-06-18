#include <stdio.h>
#include <stdlib.h>

#include <render.h>

frame_t* frame_buffer;

triangle_3d_t tri = 
{
    .v0 = {-1.0, 1.0, 0.0},
    .v1 = {0.0, -1.0, 0.0},
    .v2 = {1.0, 1.0, 0.0}
};

void shader(vec3_t* vert)
{
    vert->x *= 0.4;
    vert->y *= 0.4;
}

int main(int argc, char* argv)
{
    frame_buffer = create_frame(24, 12);

    poly_t poly;
    poly.data = &tri;
    poly.n = 1;
    
    clear_frame(frame_buffer, '.');

    render_poly(frame_buffer, &poly, shader);

    present_frame(frame_buffer);

    delete_frame(frame_buffer);

    return 0;
}
