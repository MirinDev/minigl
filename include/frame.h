#ifndef FRAME_H_
#define FRAME_H_

#include <stdlib.h>
#include <string.h>

#include "terminal.h"

typedef struct 
{
    char* data;
    float* z_data;
    int width, height;
} frame_t;

typedef enum FRAME_BUFFER_e
{
    FRAME_CHARACTER_BUFFER = 0b01,
    FRAME_DEPTH_BUFFER = 0b10,
} FRAME_BUFFER_t;

frame_t* create_frame(int width, int height, FRAME_BUFFER_t flags);
void delete_frame(frame_t* frame);

void clear_frame(frame_t* frame, char ch);
void present_frame(frame_t* frame);

#endif