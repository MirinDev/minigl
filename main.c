#include <render.h>
#include <objread.h>
#include <stdbool.h>

poly_t* poly;

frame_t* shadow_buffer;
mat4_t light_cam;

frame_t* frame_buffer;
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
    vec4_t vec;
    vec.x = verts[0].x * a + verts[1].x * b + verts[2].x * g;
    vec.y = verts[0].y * a + verts[1].y * b + verts[2].y * g;
    vec.z = verts[0].z * a + verts[1].z * b + verts[2].z * g;
    vec.w = verts[0].w * a + verts[1].w * b + verts[2].w * g;
    vec = divide_vector_4_float(vec, vec.w);

    vec.x = (vec.x + 1.0) * shadow_buffer->width / 2.0f;
    vec.y = (vec.y + 1.0) * shadow_buffer->height / 2.0f;

    float shadow_z = shadow_buffer->z_data[(int)vec.y * shadow_buffer->width + (int)vec.x];

    if (vec.z < shadow_z + 0.005f)
        *ch = '#';
    else
        *ch = '.';
}

int main(int argc, char* argv[])
{
    init_terminal();
    hide_cursor();
    set_terminal_title("generic title test");
    clear_terminal();
    set_cursor_color(cyan);

    poly = read_obj("./assets/yememi.obj");

    frame_buffer = create_frame(64 * 2, 32 * 2, FRAME_CHARACTER_BUFFER | FRAME_DEPTH_BUFFER);

    vec3_t cam_pos = {0.0f, -3.0f, -4.0f};
    //vec3_t cam_pos = {0.0f, -3.0f, -8.0f};
    vec3_t cam_front = {0.0f, 0.0f, 1.0f};
    vec3_t cam_up = {0.0f, 1.0f, 0.0f};

    mat4_t proj = create_perspective_matrix_4x4(deg_to_rad(90.0f), 1.0f, 0.1f, 100.0f);
    mat4_t view = create_look_at_matrix_4x4(cam_pos, add_vector_3(cam_pos, cam_front), cam_up);
    cam = multiply_matrix_4x4(proj, view);

    shadow_buffer = create_frame(128, 128, FRAME_DEPTH_BUFFER);

    mat4_t light_proj = create_orthographic_matrix_4x4(-4.0f, 4.0f, 4.0f, -4.0f, 0.1f, 100.0f);
    mat4_t light_view = create_look_at_matrix_4x4((vec3_t){4.0f, -4.0f, 4.0f}, (vec3_t){0.0f, 0.0f, 0.0f}, (vec3_t){0.0f, 0.0f, 1.0f});
    light_cam = multiply_matrix_4x4(light_proj, light_view);

    model = create_transform_matrix_4x4((vec3_t){0.0f, 0.0f, 0.0f}, (vec3_t){deg_to_rad(180.0f), 0.0f, 0.0f}, (vec3_t){2.0f, 2.0f, 2.0f});
    //model = create_transform_matrix_4x4((vec3_t){0.0f, 0.0f, 0.0f}, (vec3_t){deg_to_rad(180.0f), 0.0f, 0.0f}, (vec3_t){0.1f, 0.1f, 0.1f});

    bool loop = true;
    ACTUAL_CULLIN = CULLIN_FACE_BACK;

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

        model = rotate_matrix_4x4(model, (vec3_t){0.0f, deg_to_rad(0.1f), 0.0f});

        clear_frame(shadow_buffer, 0);
        render_poly(shadow_buffer, poly, v_shadow_shader, NULL);

        clear_frame(frame_buffer, ' ');
        render_poly(frame_buffer, poly, v_shader, f_shader);

        present_frame(frame_buffer);

        usleep(1000);
    }

    delete_frame(shadow_buffer);
    delete_frame(frame_buffer);

    show_cursor();
    exit_terminal();

    return 0;
}
