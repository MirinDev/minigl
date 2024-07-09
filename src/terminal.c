#include <terminal.h>

#ifdef __linux__

struct termios original_terminal;

void init_terminal()
{
    tcgetattr(STDIN_FILENO, &original_terminal);
    struct termios terminal = original_terminal;

    terminal.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
}

void exit_terminal()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &original_terminal);
    set_cursor_color(0);
    clear_terminal();
}

int kbhit()
{
    int old = fcntl(STDIN_FILENO, F_GETFL, 0);

    fcntl(STDIN_FILENO, F_SETFL, old | O_NONBLOCK);
    int ch = getch();
    fcntl(STDIN_FILENO, F_SETFL, old);

    if(ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

void gotoxy(int x, int y)
{
    printf("%c[%d;%df", 0x1B, y, x);
}

void clear_terminal()
{
    printf("\e[H\033[J");
}

void hide_cursor()
{
    printf("\e[?25l");
}

void show_cursor()
{
    printf("\e[?25h");
}

void set_terminal_title(char* title)
{
    printf("\e]0;%s\a", title);
}

void set_cursor_color(int color)
{
    printf("\e[0;%dm", color);
}

void set_background_color(int color)
{
    printf("\e[%dm", color + 10);
}

#else

void init_terminal()
{
    //
}

void exit_terminal()
{
    //
}

void gotoxy(int x, int y)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;
    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(handle, coord);
}

void clear_terminal()
{
    system ("cls");
}

void hide_cursor()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo (handle, &info);
    info.bVisible = FALSE;
    SetConsoleCursorInfo (handle, &info);
}

void show_cursor()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo (handle, &info);
    info.bVisible = TRUE;
    SetConsoleCursorInfo (handle, &info);
}

void set_terminal_title(char* title)
{
    SetConsoleTitle(title);
}

void set_cursor_color(int color)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, color);
}

void set_background_color(int color)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, color + 16);
}

#endif