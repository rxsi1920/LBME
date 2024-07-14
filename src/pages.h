#ifndef __PAGES_H__
#define __PAGES_H__

#include <ncurses.h>

void draw_help_page();
void draw_home_page();
void draw_settings_page();
void draw_battery_info();
void draw_page_keymap(char* menu[], char* keys[], int len);
void setup_pages();
void clean_pages();

#endif