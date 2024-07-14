#include "pages.h"
#include "screen.h"
#include "battery.h"

#include <malloc.h>
#include <math.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define HOME_LEN 3
#define SETTINGS_LEN 3
#define PG_BROWSER_LEN 3

static char *home_menu[] = {"Help", "Setup", "Quit"};
static char *home_menu_keys[] = {"F1", "F2", "F10"};

static char *settings_page[] = {"General", "Themes", "About"};

static char *page_browser[] = {"Next Selection", "Depth", "Enter"};
static char *page_browser_keys[] = {"^/⌄", "</>", "Check/Uncheck/Select"};

static struct winsize dim;
static struct battery_status *status;

void (*fn_ptr)();

void get_fn()
{
}

void setup_pages()
{
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &dim);

    status = (struct battery_status *)malloc(sizeof(battery_status));
    scrape_battery_info(status);
}

void clean_pages()
{
    free(status);
}

void draw_help_page()
{
    WINDOW *menuwin = newwin(6, 12, 8, 5);
    box(menuwin, 0, 0);
    wrefresh(menuwin);
}

void draw_battery_info()
{

    scrape_battery_info(status);
    WINDOW *inf_ = newwin(4, dim.ws_col - 1, 0, 0);
    keypad(inf_, TRUE);
    wrefresh(inf_);

    wattrset(inf_, COLOR_PAIR(2));
    wprintw(inf_, "DEVICE: ");
    wattrset(inf_, COLOR_PAIR(0));
    wprintw(inf_, "%s ", status->name);

    wattrset(inf_, COLOR_PAIR(2));
    wprintw(inf_, "MANUFACTURER: ");
    wattrset(inf_, COLOR_PAIR(0));
    wprintw(inf_, "%s ", status->manufacturer);

    wattrset(inf_, COLOR_PAIR(2));
    wprintw(inf_, "MODEL: ");
    wattrset(inf_, COLOR_PAIR(0));
    wprintw(inf_, "%s ", status->model_name);

    wattrset(inf_, COLOR_PAIR(2));
    wprintw(inf_, "STATE: ");
    if (strcmp(status->state, "FULL") == 0)
        wattrset(inf_, COLOR_PAIR(3));
    else if (strcmp(status->state, "DISCHARGING") == 0)
        wattrset(inf_, COLOR_PAIR(4));
    else if (strcmp(status->state, "CHARGING") == 0)
        wattrset(inf_, COLOR_PAIR(6));
    else
        wattrset(inf_, COLOR_PAIR(0));
    // else if (strcmp(status->state, "FULL") == 0)
    wprintw(inf_, "%s ", status->state);

    wattrset(inf_, COLOR_PAIR(2));
    wprintw(inf_, "CHARGE: ");
    wattrset(inf_, COLOR_PAIR(0));
    wprintw(inf_, "[");

    int bars = floor(status->battery / 5);
    bars -= bars % 20;
    int rem_bars = 20 - bars;

    if (bars >= 15)
        wattrset(inf_, COLOR_PAIR(3));
    else if (bars >= 12)
        wattrset(inf_, COLOR_PAIR(2));
    else if (bars >= 8)
        wattrset(inf_, COLOR_PAIR(4));
    else if (bars >= 0)
        wattrset(inf_, COLOR_PAIR(5));

    for (int i = 0; i < bars; i++)
        wprintw(inf_, "❙");
    wattrset(inf_, COLOR_PAIR(0));
    for (int i = 0; i < rem_bars; i++)
        wprintw(inf_, " ");
    wprintw(inf_, "]");

    wrefresh(inf_);
}

void draw_page_keymap(char *menu[], char *keys[], int len)
{
    struct winsize dim;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &dim);

    WINDOW *keymap = newwin(1, dim.ws_col - 1, dim.ws_row - 1, 0);
    keypad(keymap, TRUE);
    wrefresh(keymap);

    for (int i = 0; i < len; i++)
    {
        wattrset(keymap, COLOR_PAIR(0));
        wprintw(keymap, "%s", keys[i]);
        wattrset(keymap, A_STANDOUT | COLOR_PAIR(1));
        wprintw(keymap, "%-7s", menu[i]);
    }
    unsigned short x, y;
    getyx(keymap, y, x);
    mvwchgat(keymap, 0, x, -1, A_STANDOUT, 1, NULL);
    refresh();
    unsigned short key = wgetch(keymap);
    switch (key)
    {
    case 27: // Escape key
    case 'q':
    case 'Q':
    case KEY_F(10):
        close_screen();
        break;
    case KEY_F(1):
    case 'h':
        break;
    case KEY_F(2):
        break;
    case KEY_F(12):
        break;
    default:
        break;
    }

    wrefresh(keymap);
}

void draw_home_page()
{
    refresh();
    draw_battery_info();
    draw_page_keymap(home_menu, home_menu_keys, HOME_LEN);
}

void draw_settings_page()
{
    draw_page_keymap(page_browser, page_browser_keys, PG_BROWSER_LEN);
}