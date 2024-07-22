#include "app_info.h"
#include "pages.h"
#include "screen.h"
#include "battery.h"
#include "util.h"

#include <malloc.h>
#include <math.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static char *home_menu[] = {"Help", "Setup", "Toggle Graph", "Quit", "About"};
static char *home_menu_keys[] = {"F1", "F2", "F8", "F10", "F12"};

static char *settings_tabs[] = {"General", "Themes", "About"};

static char *page_browser[] = {"Next Category", "Depth", "Check/Uncheck/Select", "Exit", "Save"};
static char *page_browser_keys[] = {"↕", "↔", "Enter", "F10", "F12"};

int setup_selection = 0;

WINDOW *active_windows[10];
bool settings_open = false;

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

void refresh_screen()
{
  // for(int i=0; i < get_length2(active_windows); i++)
  // {
  //   delwin(active_windows[i]);
  // }
  endwin();
  erase();
  // memset(active_windows, 0, sizeof active_windows);
}

void draw_help_page()
{
}

void draw_battery_info()
{
  scrape_battery_info(status);
  WINDOW *device_inf = newwin(1, dim.ws_col - 1, 0, 0);
  keypad(device_inf, TRUE);
  wrefresh(device_inf);

  WINDOW *stat_inf = newwin(1, dim.ws_col - 1, 1, 0);
  keypad(stat_inf, TRUE);
  wrefresh(stat_inf);

  wattrset(device_inf, COLOR_PAIR(2));
  wprintw(device_inf, "DEVICE: ");
  wattrset(device_inf, COLOR_PAIR(0));
  wprintw(device_inf, "%s ", status->name);

  wattrset(device_inf, COLOR_PAIR(2));
  wprintw(device_inf, "MANUFACTURER: ");
  wattrset(device_inf, COLOR_PAIR(0));
  wprintw(device_inf, "%s ", status->manufacturer);

  wattrset(device_inf, COLOR_PAIR(2));
  wprintw(device_inf, "MODEL: ");
  wattrset(device_inf, COLOR_PAIR(0));
  wprintw(device_inf, "%.15s", status->model_name);
  wprintw(device_inf, "%.15s", status->model_name);

  if (sizeof(status->model_name) > 15)
    wprintw(device_inf, "...");
  wprintw(device_inf, " ");

  wattrset(stat_inf, COLOR_PAIR(2));
  wprintw(stat_inf, "STATE: ");
  if (strcmp(status->state, "FULL") == 0)
    wattrset(stat_inf, COLOR_PAIR(3));
  else if (strcmp(status->state, "DISCHARGING") == 0)
    wattrset(stat_inf, COLOR_PAIR(4));
  else if (strcmp(status->state, "CHARGING") == 0)
    wattrset(stat_inf, COLOR_PAIR(6));
  else
    wattrset(stat_inf, COLOR_PAIR(0));
  // else if (strcmp(status->state, "FULL") == 0)
  wprintw(stat_inf, "%-11s ", status->state);

  wattrset(stat_inf, COLOR_PAIR(2));
  wprintw(stat_inf, "CHARGE: ");
  wattrset(stat_inf, COLOR_PAIR(0));
  wprintw(stat_inf, "[");

  int bars = floor(status->battery / 5);
  bars -= bars % 20;
  int rem_bars = 20 - bars;

  if (bars >= 15)
    wattrset(stat_inf, COLOR_PAIR(3));
  else if (bars >= 12)
    wattrset(stat_inf, COLOR_PAIR(2));
  else if (bars >= 8)
    wattrset(stat_inf, COLOR_PAIR(4));
  else if (bars >= 0)
    wattrset(stat_inf, COLOR_PAIR(5));

  for (int i = 0; i < bars; i++)
    wprintw(stat_inf, "❙");
  wattrset(stat_inf, COLOR_PAIR(0));
  for (int i = 0; i < rem_bars; i++)
    wprintw(stat_inf, " ");
  wprintw(stat_inf, "]");

  wprintw(stat_inf, "%4d%% ", status->battery);

  wattrset(stat_inf, COLOR_PAIR(2));
  wprintw(stat_inf, "UPTIME: ");
  wattrset(stat_inf, COLOR_PAIR(0));
  wprintw(stat_inf, "%4ld:%02d:%02d", status->uptime_h, status->uptime_m, status->uptime_s);

  wrefresh(device_inf);
  wrefresh(stat_inf);
  doupdate();
}

WINDOW *draw_page_keymap(char *menu[], char *keys[], int len)
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
    wprintw(keymap, "%-6s ", menu[i]);
  }
  unsigned short x, y;
  getyx(keymap, y, x);
  mvwchgat(keymap, 0, x, -1, A_STANDOUT, 1, NULL);
  refresh();
  wrefresh(keymap);

  return keymap;
}

void draw_home_page()
{
  WINDOW *menu = draw_page_keymap(home_menu, home_menu_keys, HOME_LEN);
  unsigned short key = wgetch(menu);
  switch (key)
  {
  case KEY_RESIZE:
    refresh_screen();
    break;
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
    settings_open = true;
    break;
  case KEY_F(12):
    settings_open = true;
    setup_selection = 2;
    break;
  default:
    break;
  }
  wrefresh(menu);
  refresh();
}

void draw_settings_page()
{
  WINDOW *menu = newwin(6, 24, 3, 0);
  keypad(menu, TRUE);
  wattrset(menu, A_STANDOUT | COLOR_PAIR(6));
  mvwprintw(menu, 0, 0, " %-18s", "Setup Categories");
  wattrset(menu, COLOR_PAIR(0));
  for (int i = 0; i < SETTINGS_LEN; i++)
  {
    if (setup_selection == i)
    {
      wattrset(menu, A_STANDOUT | COLOR_PAIR(4));
      mvwprintw(menu, i + 1, 0, " %-18s", settings_tabs[i]);
      wattrset(menu, COLOR_PAIR(0));
    }
    else
      mvwprintw(menu, i + 1, 0, " %-18s", settings_tabs[i]);
  }
  wrefresh(menu);
  switch (setup_selection)
  {
  case 0:
    show_general_settings();
    break;
  case 1:
    show_theme_settings();
    break;
  case 2:
    show_about_tab();
    break;
  }
  draw_page_keymap(page_browser, page_browser_keys, PG_BROWSER_LEN);
  unsigned short key = wgetch(menu);
  switch (key)
  {
  case KEY_RESIZE:
    refresh_screen();
    break;
  case 27: // Escape key
  case KEY_F(2):
  case KEY_F(10):
    settings_open = false;
    refresh_screen();
    break;
  case 'q':
  case 'Q':
    close_screen();
    break;
  case KEY_F(1):
  case 'h':
    break;
  case KEY_F(12):
    break;
  case KEY_UP:
    if (setup_selection > 0)
      setup_selection--;
    refresh_screen();
    break;
  case KEY_DOWN:
    if (setup_selection < SETTINGS_LEN - 1)
      setup_selection++;
    refresh_screen();
    break;
  case KEY_LEFT:
    break;
  case KEY_RIGHT:
    break;
  default:
    break;
  }
  refresh();
}

void draw_tab_header(char *header)
{
  WINDOW *general_tab_header = newwin(1, dim.ws_col, 3, 20);
  wattrset(general_tab_header, A_STANDOUT | COLOR_PAIR(6));
  mvwprintw(general_tab_header, 0, 0, " %-30s", header);
  wattrset(general_tab_header, COLOR_PAIR(0));
  unsigned short x, y;
  getyx(general_tab_header, y, x);
  mvwchgat(general_tab_header, 0, x, -1, A_STANDOUT, 6, NULL);
  wrefresh(general_tab_header);
}

void show_general_settings()
{
  draw_tab_header("General");
}

void show_theme_settings()
{
  draw_tab_header("Themes");
}

void show_about_tab()
{
  draw_tab_header("About");
  WINDOW *content = newwin(dim.ws_row - 1, dim.ws_col - 21, 4, 21);
  mvwprintw(content, 0, 0, "%s",
            "\nLBMe Version: " LBME_VERSION " (2024)\n"
            "\nCheck out the Github project here: https://github.com/rxsi1920/LBME \n"
            "Created by Preran Apinakoppa. Inspired by Nvtop and Htop.");
  wrefresh(content);
}