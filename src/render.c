#include <render.h>

void render_poly(frame_t* frame, poly_t* poly, vertex_shader v_shader, fragment_shader f_shader)
{
    for (unsigned int i = 2; i < poly->n; i += 3)
    {
        triangle_3d_t ot;

        for (unsigned int j = 0; j < 3; j++)
        {
            ot.data[j] = vec3_to_vec4(poly->data[poly->inds[i - j]], 1.0);
            v_shader(&ot.data[j], i, j);
        }

        raster_triangle(frame, ot, f_shader);
    }
}
