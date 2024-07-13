#include <frame.h>

frame_t* create_frame(int width, int height, FRAME_BUFFER_t flags)
{
    frame_t* frame = (frame_t*)malloc(sizeof(frame_t));
    frame->width = width;
    frame->height = height;

    if (flags & FRAME_CHARACTER_BUFFER)
        frame->data = (char*)malloc(frame->width * frame->height * sizeof(char));
    else
        frame->data = NULL;
    
    if (flags & FRAME_DEPTH_BUFFER)
        frame->z_data = (float*)malloc(frame->width * frame->height * sizeof(float));
    else
        frame->z_data = NULL;
    
    return frame;
}

void delete_frame(frame_t* frame)
{
    if (frame == NULL) return;

    if (frame->data)
        free(frame->data);
    
    if (frame->z_data)
        free(frame->z_data);

    free(frame);
}

void clear_frame(frame_t* frame, char ch)
{
    if (frame == NULL) return;

    if (frame->data)
        memset(frame->data, ch, frame->width * frame->height * sizeof(char));
    
    if (frame->z_data)
    {
        for (int i = 0; i < frame->width * frame->height; i++)
        frame->z_data[i] = 1.0f;
    }
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
