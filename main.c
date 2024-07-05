#include <render.h>
#include <objread.h>

frame_t* frame_buffer;
zframe_t* zbuffer;

poly_t* poly;

mat4_t cam;
mat4_t model;

void v_shader(vec4_t* vert, int i, int j)
{
    vec4_t world_vertice = multiply_matrix_4x4_vector4(model, *vert);
    *vert = multiply_matrix_4x4_vector4(cam, world_vertice);
}

void f_shader(char* ch, float a, float b, float g)
{
    *ch = '#';
}

int main(int argc, char* argv[])
{
    init_terminal();
    hide_cursor();

    set_terminal_title("eu sou gay");

    frame_buffer = create_frame(64, 32);
    zbuffer = create_zframe(64, 32);

    poly = read_obj("./assets/cube.obj");

    mat4_t proj = perspective(deg_to_rad(90.0f), 1.0f, 0.1f, 100.0f);
    //mat4_t proj = orthographic(-1.0f, 1.0f, 1.0f, -1.0f, 0.1f, 100.0f);
    mat4_t view = identity_matrix_4x4();
    cam = multiply_matrix_4x4(proj, view);

    model = identity_matrix_4x4();
    model = translate_matrix_4x4(model, (vec3_t){0.0f, 0.0f, -4.0f});
    //model = scale_matrix_4x4(model, (vec3_t){0.1f, 0.1f, 0.1f});
    model = rotate_with_deg_matrix_4x4(model, (vec3_t){180.0, 0.0, 0.0});

    clear_terminal();
    set_cursor_color(cyan);

    int loop = 1;

    while (loop)
    {
        while (kbhit())
        {
            char ch = getch();
            if (ch == 'q')
            {
                loop = 0;
                break;
            }
        }

        model = rotate_with_deg_matrix_4x4(model, (vec3_t){0.0, 0.1, 0.0});

        clear_frame(frame_buffer, '.');
        clear_zframe(zbuffer);

        render_poly(frame_buffer, zbuffer, poly, v_shader, f_shader);
        present_frame(frame_buffer);

        usleep(1000);
    }

    delete_zframe(zbuffer);
    delete_frame(frame_buffer);

    //set_cursor_color(0);
    clear_terminal();
    show_cursor();
    exit_terminal();

    return 0;
}
