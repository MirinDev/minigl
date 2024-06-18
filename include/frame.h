#ifndef FRAME_H_
#define FRAME_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    char* data;
    int width, height;
} frame_t;

frame_t* create_frame(int width, int height);
void delete_frame(frame_t* frame);

void clear_frame(frame_t* frame, char ch);
void present_frame(frame_t* frame);

#endif