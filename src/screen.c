#include "screen.h"

#include <ncurses.h>

int make_screen()
{
    initscr();
    cbreak();
}

int close_screen()
{
    endwin();
}