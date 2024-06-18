#include <frame.h>

frame_t* create_frame(int width, int height)
{
    frame_t* frame = (frame_t*)malloc(sizeof(frame_t));
    frame->width = 25;
    frame->height = 12;

    frame->data = (char*)malloc(frame->width * frame->height * sizeof(char));
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
        memcpy(line, frame->data + y * frame->width * sizeof(char), frame->width * sizeof(char));
        fprintf(stdout, "%s\n", line);
    }
}