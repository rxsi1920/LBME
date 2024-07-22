#ifndef __PAGES_H__
#define __PAGES_H__

#include <ncurses.h>

#define HOME_LEN 5
#define SETTINGS_LEN 3
#define PG_BROWSER_LEN 5

typedef struct current_page {
  char *menu;
  char *keys;
  void (*func);
} current_page;

extern bool settings_open;

void draw_help_page();
void draw_home_page();
void draw_settings_page();
void draw_battery_info();
WINDOW *draw_page_keymap(char* menu[], char* keys[], int len);
void show_general_settings();
void show_theme_settings();
void show_about_tab();
void setup_pages();
void clean_pages();
void refresh_screen();

#endif