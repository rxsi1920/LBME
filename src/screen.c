#include "screen.h"
#include "pages.h"

#include <curses.h>
#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>

int make_screen()
{
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    cbreak();
    refresh();
    curs_set(0);
    keypad(stdscr, 1);

    // Enable coloring
    start_color();
    use_default_colors();

    // Initialize the colors
    init_pair(0, -1, -1);
    init_pair(1, COLOR_BLUE, COLOR_WHITE);
    init_pair(2, COLOR_BLUE, -1);
    init_pair(3, COLOR_GREEN, -1);
    init_pair(4, COLOR_YELLOW, -1);
    init_pair(5, COLOR_RED, -1);
    init_pair(6, COLOR_CYAN, -1);

    setup_pages();

}

int close_screen()
{
    clean_pages();
    endwin();
    exit(0);
}