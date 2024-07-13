#ifndef FRAME_H_
#define FRAME_H_

#include <stdlib.h>
#include <string.h>

#include "terminal.h"

typedef struct 
{
    char* data;
    int width, height;
} frame_t;

typedef struct 
{
    float* data;
    int width, height;
} zframe_t;

frame_t* create_frame(int width, int height);
void delete_frame(frame_t* frame);
void clear_frame(frame_t* frame, char ch);
void present_frame(frame_t* frame);

zframe_t* create_zframe(int width, int height);
void delete_zframe(zframe_t* zframe);
void clear_zframe(zframe_t* zframe);
void present_zframe(zframe_t* zframe);

#endif