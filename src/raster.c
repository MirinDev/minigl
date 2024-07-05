#include <raster.h>

float edge_cross(vec2_t a, vec2_t b, vec2_t p)
{
    vec2_t ab = {b.x - a.x, b.y - a.y};
    vec2_t ap = {p.x - a.x, p.y - a.y};
    
    return ab.x * ap.y - ab.y * ap.x;
}

float minf(float a, float b)
{
    return a < b ? a : b;
}

float maxf(float a, float b)
{
    return a > b ? a : b;
}

float clampf(float a, float b, float c)
{
    return a < b ? b : a > c ? c : a;
}

void raster_triangle(frame_t* frame, zframe_t* zframe, triangle_3d_t tri, fragment_shader shader)
{
    int min_x = (int)clampf(minf(minf(tri.v0.x, tri.v1.x), tri.v2.x), 0, frame->width);
    int min_y = (int)clampf(minf(minf(tri.v0.y, tri.v1.y), tri.v2.y), 0, frame->height);

    int max_x = (int)clampf(maxf(maxf(tri.v0.x, tri.v1.x), tri.v2.x), 0, frame->width);
    int max_y = (int)clampf(maxf(maxf(tri.v0.y, tri.v1.y), tri.v2.y), 0, frame->height);

    vec2_t v0 = {tri.v0.x, tri.v0.y};
    vec2_t v1 = {tri.v1.x, tri.v1.y};
    vec2_t v2 = {tri.v2.x, tri.v2.y};
    
    float abc = edge_cross(v0, v1, v2);

    vec2_t p = {min_x, min_y};
    float pbc = edge_cross(p, v1, v2);
    float apc = edge_cross(v0, p, v2);
    float abp = edge_cross(v0, v1, p);

    vec2_t pbc_delta = {v2.x - v1.x, v1.y - v2.y};
    vec2_t apc_delta = {v0.x - v2.x, v2.y - v0.y};
    vec2_t abp_delta = {v1.x - v0.x, v0.y - v1.y};

    for (int y = min_y; y <= max_y; y++)
    {
        float a = pbc;
        float b = apc;
        float g = abp;

        for (int x = min_x; x <= max_x; x++)
        {
            float alpha = a / abc;
            float beta = b / abc;
            float gama = g / abc;
            
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