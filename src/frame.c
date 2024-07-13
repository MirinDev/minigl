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

    for (int y = 0; y < frame->height; y++)
    {
        gotoxy(0, y);
        fwrite(frame->data + y * frame->width, sizeof(char), frame->width, stdout);
    }

    fflush(stdout);
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

void present_zframe(zframe_t* zframe)
{
    if (zframe == NULL) return;

    for (int y = 0; y < zframe->height; y++)
    {
        gotoxy(0, y);
        for (int x = 0; x < zframe->width; x++)
            printf("%.2f ", *(zframe->data + y * zframe->width + x));
    }

    fflush(stdout);
}