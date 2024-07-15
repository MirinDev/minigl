#include <raster.h>

float edge_cross(vec2_t a, vec2_t b, vec2_t p)
{
    vec2_t ab = {b.x - a.x, b.y - a.y};
    vec2_t ap = {p.x - a.x, p.y - a.y};
    
    return ab.x * ap.y - ab.y * ap.x;
}

CULLIN_FACE_t ACTUAL_CULLIN = CULLIN_FACE_NONE;

void raster_triangle(frame_t* frame, triangle_3d_t tri, fragment_shader shader)
{
    float sx = (float)frame->width / 2;
    float sy = (float)frame->height / 2;

    vec2_t v0 = {(tri.v0.x / tri.v0.w + 1.0f) * sx, (tri.v0.y / tri.v0.w + 1.0f) * sy};
    float z0 = tri.v0.z / tri.v0.w;
    vec2_t v1 = {(tri.v1.x / tri.v1.w + 1.0f) * sx, (tri.v1.y / tri.v1.w + 1.0f) * sy};
    float z1 = tri.v1.z / tri.v1.w;
    vec2_t v2 = {(tri.v2.x / tri.v2.w + 1.0f) * sx, (tri.v2.y / tri.v2.w + 1.0f) * sy};
    float z2 = tri.v2.z / tri.v2.w;

    int min_x = (int)clampf(minf(minf(v0.x, v1.x), v2.x), 0, frame->width - 1);
    int min_y = (int)clampf(minf(minf(v0.y, v1.y), v2.y), 0, frame->height - 1);

    int max_x = (int)clampf(maxf(maxf(v0.x, v1.x), v2.x), 0, frame->width - 1);
    int max_y = (int)clampf(maxf(maxf(v0.y, v1.y), v2.y), 0, frame->height - 1);
    
    float abc = edge_cross(v0, v1, v2);

    switch (ACTUAL_CULLIN)
    {
    case CULLIN_FACE_NONE:
        break;
    
    case CULLIN_FACE_FRONT:
        if (abc > 0.0f) return;
        break;
    
    case CULLIN_FACE_BACK:
        if (abc < 0.0f) return;
        break;
    
    default:
        break;
    }

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
                if (frame->z_data != NULL)
                {
                    float z = z0 * alpha + z1 * beta + z2 * gama;

                    if (z > -1.0f && z < frame->z_data[y * frame->width + x])
                    {
                        frame->z_data[y * frame->width + x] = z;
                        
                        if (frame->data != NULL)
                        {
                            float w = alpha / tri.v0.w + beta / tri.v1.w + gama / tri.v2.w;
                            alpha /= (tri.v0.w * w);
                            beta /= (tri.v1.w * w);
                            gama /= (tri.v2.w * w);

                            char ch = ' ';
                            shader(&ch, alpha, beta, gama);
                            frame->data[y * frame->width + x] = ch;
                        }
                    }
                }
                else if (frame->data != NULL)
                {
                    char ch = ' ';
                    shader(&ch, alpha, beta, gama);
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