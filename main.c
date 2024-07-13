#include <render.h>
#include <objread.h>
#include <stdbool.h>

frame_t* frame_buffer;
zframe_t* zbuffer;

poly_t* poly;
poly_t* cube;

zframe_t* shadow_buffer;
mat4_t light_cam;

mat4_t cam;
mat4_t model;

vec4_t verts[3];

void v_shader(vec4_t* vert, int i, int j)
{
    vec4_t world_vertice = multiply_matrix_4x4_vector4(model, *vert);
    *vert = multiply_matrix_4x4_vector4(cam, world_vertice);
    
    verts[j] = multiply_matrix_4x4_vector4(light_cam, world_vertice);
}

void v_shadow_shader(vec4_t* vert, int i, int j)
{
    vec4_t world_vertice = multiply_matrix_4x4_vector4(model, *vert);
    *vert = multiply_matrix_4x4_vector4(light_cam, world_vertice);
}

void f_shader(char* ch, float a, float b, float g)
{
    float x = verts[0].x * a + verts[1].x * b + verts[2].x * g;
    float y = verts[0].y * a + verts[1].y * b + verts[2].y * g;
    float z = verts[0].z * a + verts[1].z * b + verts[2].z * g;
    float w = verts[0].w * a + verts[1].w * b + verts[2].w * g;
    x /= w;
    y /= w;
    z /= w;

    x = (x + 1.0) * shadow_buffer->width / 2.0f;
    y = (y + 1.0) * shadow_buffer->height / 2.0f;

    float shadow_z = shadow_buffer->data[(int)y * shadow_buffer->width + (int)x];

    if (z < shadow_z + 0.005)
        *ch = '#';
    else
        *ch = '.';
}

int main(int argc, char* argv[])
{
    init_terminal();
    hide_cursor();

    set_terminal_title("generic title test");

    frame_buffer = create_frame(64 * 4, 32 * 4);
    zbuffer = create_zframe(64 * 4, 32 * 4);

    poly = read_obj("./assets/yememi.obj");

    mat4_t proj = perspective(deg_to_rad(90.0f), 1.0f, 0.1f, 100.0f);
    mat4_t view = identity_matrix_4x4();
    view = translate_matrix_4x4(view, (vec3_t){0.0f, 1.0f, -4.0f});
    cam = multiply_matrix_4x4(proj, view);

    shadow_buffer = create_zframe(128, 128);

    mat4_t light_proj = orthographic(-4.0f, 4.0f, 4.0f, -4.0f, 0.1f, 100.0f);
    mat4_t light_view = identity_matrix_4x4();
    light_view = translate_matrix_4x4(light_view, (vec3_t){0.0f, 0.0f, -8.0f});
    light_view = rotate_with_deg_matrix_4x4(light_view, (vec3_t){-45.0, -45.0, 0.0});

    light_cam = multiply_matrix_4x4(light_proj, light_view);

    mat4_t model_poly = identity_matrix_4x4();
    model_poly = rotate_with_deg_matrix_4x4(model_poly, (vec3_t){180.0, 180.0, 0.0});
    model_poly = scale_matrix_4x4(model_poly, (vec3_t){2.0f, 2.0f, 2.0f});
    //model_poly = scale_matrix_4x4(model_poly, (vec3_t){0.1f, 0.1f, 0.1f});

    clear_terminal();
    set_cursor_color(cyan);
    //set_background_color(gray);

    bool loop = true;

    while (loop)
    {
        while (kbhit())
        {
            char ch = getch();
            switch (ch)
            {
            case 'q':
                loop = false;
                break;
            
            default:
                break;
            }
        }

        model_poly = rotate_with_deg_matrix_4x4(model_poly, (vec3_t){0.0f, 0.1f, 0.0f});

        clear_frame(frame_buffer, ' ');
        clear_zframe(zbuffer);
        clear_zframe(shadow_buffer);

        model = model_poly;
        render_poly(NULL, shadow_buffer, poly, v_shadow_shader, NULL);
        render_poly(frame_buffer, zbuffer, poly, v_shader, f_shader);

        present_frame(frame_buffer);

        usleep(1000);
    }

    delete_zframe(zbuffer);
    delete_frame(frame_buffer);

    show_cursor();
    exit_terminal();

    return 0;
}
