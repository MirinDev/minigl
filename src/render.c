#include <render.h>

void render_poly(frame_t* frame, poly_t* poly, vertex_shader shader)
{
    float sx = (float)frame->width / 2;
    float sy = (float)frame->height / 2;

    for (size_t i = 0; i < poly->n; i++)
    {
        triangle_3d_t* it = &poly->data[i];
        triangle_2d_t ot;

        for (size_t j = 0; j < 3; j++)
        {
            shader(&it->data[j]);

            ot.data[j].x = (int)((it->data[j].x + 1.0) * sx);
            ot.data[j].y = (int)((it->data[j].y + 1.0) * sy);
        }

        raster_triangle(frame, ot);
    }
}