#include <raster.h>

int edge_cross(vec2i_t a, vec2i_t b, vec2i_t p)
{
    vec2i_t ab = {b.x - a.x, b.y - a.y};
    vec2i_t ap = {p.x - a.x, p.y - a.y};
    
    return ab.x * ap.y - ab.y * ap.x;
}

void raster_triangle(frame_t* frame, zframe_t* zframe, triangle_3d_t tri, fragment_shader shader)
{
    vec2i_t v0 = {tri.v0.x, tri.v0.y};
    vec2i_t v1 = {tri.v1.x, tri.v1.y};
    vec2i_t v2 = {tri.v2.x, tri.v2.y};
    
    float abc = edge_cross(v0, v1, v2);

    vec2i_t p = {0, 0};
    float pbc = edge_cross(p, v1, v2);
    float apc = edge_cross(v0, p, v2);
    float abp = edge_cross(v0, v1, p);

    vec2i_t pbc_delta = {v2.x - v1.x, v1.y - v2.y};
    vec2i_t apc_delta = {v0.x - v2.x, v2.y - v0.y};
    vec2i_t abp_delta = {v1.x - v0.x, v0.y - v1.y};

    for (size_t y = 0; y < frame->height; y++)
    {
        int a = pbc;
        int b = apc;
        int g = abp;

        for (size_t x = 0; x < frame->width; x++)
        {
            float alpha = (float)a / (float)abc;
            float beta = (float)b / (float)abc;
            float gama = (float)g / (float)abc;

            if (alpha >= 0 && beta >= 0 && gama >= 0)
            {
                float z = tri.v0.z * alpha + tri.v1.z * beta + tri.v2.z * gama;

                if (z >= 0.0f && z < zframe->data[y * zframe->width + x])
                {
                    char ch = ' ';
                    shader(&ch, alpha, beta, gama);

                    zframe->data[y * zframe->width + x] = z;
                    frame->data[y * frame->width + x] = ch;
                }
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