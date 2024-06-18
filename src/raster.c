#include <raster.h>

int edge_cross(vec2i_t a, vec2i_t b, vec2i_t p)
{
    vec2i_t ab = {.x = b.x - a.x, .y = b.y - a.y};
    vec2i_t ap = {.x = p.x - a.x, .y = p.y - a.y};
    
    return ab.x * ap.y - ab.y * ap.x;
}

void raster_triangle(frame_t* frame, triangle_2d_t tri)
{
    float abc = edge_cross(tri.v0, tri.v1, tri.v2);

    vec2i_t p = {.x = 0, .y = 0};
    float pbc = edge_cross(p, tri.v1, tri.v2);
    float apc = edge_cross(tri.v0, p, tri.v2);
    float abp = edge_cross(tri.v0, tri.v1, p);

    vec2i_t pbc_delta = {.x = tri.v2.x - tri.v1.x, .y = tri.v1.y - tri.v2.y};
    vec2i_t apc_delta = {.x = tri.v0.x - tri.v2.x, .y = tri.v2.y - tri.v0.y};
    vec2i_t abp_delta = {.x = tri.v1.x - tri.v0.x, .y = tri.v0.y - tri.v1.y};

    for (size_t y = 0; y < frame->height; y++)
    {
        int a = pbc;
        int b = apc;
        int g = abp;

        for (size_t x = 0; x < frame->width; x++)
        {
            if (a >= 0 && b >= 0 && g >= 0)
            {
                float alpha = (float)a / (float)abc;
                float beta = (float)b / (float)abc;
                float gama = (float)g / (float)abc;

                frame->data[y * frame->width + x] = '#';
            }
            
            a += pbc_delta.y;
            b += apc_delta.y;
            g += abp_delta.y;
        }

        pbc += pbc_delta.x;
        apc += apc_delta.x;
        abp += abp_delta.x;
    }
}