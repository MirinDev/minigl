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
        white = 37,

        gray = 90,
        bright_red = 91,
        light_green = 92,
        bright_yellow = 93,
        light_blue = 94,
        bright_purple = 95,
        bright_cyan = 96,
        bright_white = 97,
    };

    /*enum modes
    {
        normal = 0,
        bold = 1,
        italic = 3,
        underline = 4,
    };*/
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

        gray = 8,
        light_blue = 9,
        light_green = 10,
        bright_cyan = 11,
        bright_red = 12,
        bright_purple = 13,
        bright_yellow = 14,
        bright_white = 15,
    };
#endif

void init_terminal();

void exit_terminal();

void hide_cursor();

void show_cursor();

void clear_terminal();

void set_cursor_color(int color);

void set_background_color(int color);

void set_terminal_title(char* title);

void gotoxy(int x, int y);

#endif