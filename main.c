#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <render.h>

frame_t* frame_buffer;
zframe_t* zbuffer;

vec3_t tri[] = 
{
    {-1.0, -1.0, 0.0},
    {1.0, -1.0, 0.0},
    {1.0, 1.0, 0.0},
    {-1.0, 1.0, 0.0},
};

vec2_t uv[] = 
{
    {0.0, 0.0},
    {1.0, 0.0},
    {1.0, 1.0},
    {0.0, 1.0},
};

unsigned int inds[] = 
{
    0, 1, 2,
    2, 3, 0,
};

mat4_t cam;
mat4_t model;

int t[3];
char tex[256] = "     $$$$$          $$$$$$$$$       ***@@*@        *@*@@@*@@@      *@**@@@*@@@     **@@@@****        @@@@@@@        **$***         ***$**$***     ****$$$$****    @@*$@$$@$*@@    @@@$$$$$$@@@    @@$$$$$$$$@@      $$$  $$$       ***    ***     ****    ****  ";

void v_shader(vec4_t* vert, int i, int j)
{
    vec4_t world_vertice = multiply_matrix_4x4_vector4(model, *vert);
    *vert = multiply_matrix_4x4_vector4(cam, world_vertice);

    t[j] = inds[i - j];
}

void f_shader(char* ch, float a, float b, float g)
{
    float u = uv[t[0]].x * a + uv[t[1]].x * b + uv[t[2]].x * g;
    float v = uv[t[0]].y * a + uv[t[1]].y * b + uv[t[2]].y * g;

    *ch = tex[(int)(v * 15.0) * 16 + (int)(u * 15.0)];
}

int main(int argc, char* argv)
{
    initscr();

    frame_buffer = create_frame(64, 32);
    zbuffer = create_zframe(64, 32);

    poly_t poly;
    poly.data = tri;
    poly.inds = inds;
    poly.n = sizeof(inds) / sizeof(*inds);

    mat4_t proj = perspective(deg_to_rad(90.0f), 1.0f, 0.1f, 100.0f);
    //mat4_t proj = orthographic(-1.0f, 1.0f, 1.0f, -1.0f, 0.1f, 100.0f);
    mat4_t view = identity_matrix_4x4();
    cam = multiply_matrix_4x4(proj, view);

    model = identity_matrix_4x4();
    model = translate_matrix_4x4(model, (vec3_t){0.0f, 0.0f, -1.0f});
    
    while (1)   
    {
        model = rotate_with_deg_matrix_4x4(model, (vec3_t){0.0, 1.0, 0.0});

        clear_frame(frame_buffer, '.');
        clear_zframe(zbuffer);

        render_poly(frame_buffer, zbuffer, &poly, v_shader, f_shader);
        present_frame(frame_buffer);

        struct timespec ts;
        ts.tv_nsec = 10000000;
        nanosleep(&ts, NULL);
    }

    delete_zframe(zbuffer);
    delete_frame(frame_buffer);

    endwin();

    return 0;
}
