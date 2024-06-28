#include <frame.h>

frame_t* create_frame(int width, int height)
{
    frame_t* frame = (frame_t*)malloc(sizeof(frame_t));
    frame->width = width;
    frame->height = height;

    frame->data = (char*)malloc(frame->width * frame->height * sizeof(char));
    
    return frame;
}

void delete_frame(frame_t* frame)
{
    if (frame == NULL) return;

    free(frame->data);
    free(frame);
}

void clear_frame(frame_t* frame, char ch)
{
    if (frame == NULL) return;

    memset(frame->data, ch, frame->width * frame->height * sizeof(char));
}

void present_frame(frame_t* frame)
{
    if (frame == NULL) return;

    char line[frame->width];
    line[frame->width] = '\0';

    for (int y = 0; y < frame->height; y++)
    {
        move(y, 0);
        memcpy(line, frame->data + y * frame->width * sizeof(char), frame->width * sizeof(char));
        printw("%s\n", line);
    }

    refresh();
}

zframe_t* create_zframe(int width, int height)
{
    zframe_t* zframe = (zframe_t*)malloc(sizeof(zframe_t));
    zframe->width = width;
    zframe->height = height;

    zframe->data = (float*)malloc(zframe->width * zframe->height * sizeof(float));

    return zframe;
}

void delete_zframe(zframe_t* zframe)
{
    if (zframe == NULL) return;

    free(zframe->data);
    free(zframe);
}

void clear_zframe(zframe_t* zframe)
{
    if (zframe == NULL) return;

    for (int i = 0; i < zframe->width * zframe->height; i++)
        zframe->data[i] = 1.0f;
}
