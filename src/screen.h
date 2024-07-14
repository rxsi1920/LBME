#ifndef __SCREEN_H__
#define __SCREEN_H__

typedef struct screen {
    char* menu_opts;
} screen;


int make_screen();
int close_screen();

#endif