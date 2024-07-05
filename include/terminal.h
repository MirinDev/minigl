#ifndef TERMINAL_H_
#define TERMINAL_H_

#include <stdio.h>

#ifdef __linux__
    #include <unistd.h>
    #include <termios.h>
    #include <fcntl.h>

    #define getch getchar
    int kbhit();

    enum colors 
    {
        black = 30,
        red = 31,
        green = 32,
        yellow = 33,
        blue = 34,
        purple = 35,
        cyan = 36,
        white = 37
    };
#else
    #include <windows.h>
    #include <conio.h>

    enum colors 
    {
        black = 0,
        blue = 1,
        green = 2,
        cyan = 3,
        red = 4,
        purple = 5,
        yellow = 6,
        white = 7,
    };
#endif

void init_terminal();

void exit_terminal();

void hide_cursor();

void show_cursor();

void clear_terminal();

void set_cursor_color(int color);

void set_terminal_title(char* title);

void gotoxy(int x, int y);

#endif