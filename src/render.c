#include <render.h>

void render_poly(frame_t* frame, zframe_t* zframe, poly_t* poly, vertex_shader v_shader, fragment_shader f_shader)
{
    float sx = (float)zframe->width / 2;
    float sy = (float)zframe->height / 2;

    for (unsigned int i = 2; i < poly->n; i += 3)
    {
        triangle_3d_t ot;

        for (unsigned int j = 0; j < 3; j++)
        {
            vec4_t v = vec3_to_vec4(poly->data[poly->inds[i - j]], 1.0);
            v_shader(&v, i, j);

            v = divide_vector_4(v, v.w);

            ot.data[j].x = (v.x + 1.0) * sx;
            ot.data[j].y = (v.y + 1.0) * sy;
            ot.data[j].z = v.z;
        }

        raster_triangle(frame, zframe, ot, f_shader);
    }
}
