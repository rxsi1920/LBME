#ifndef __UTIL_H__
#define __UTIL_H__

#include <string.h>
#include <ctype.h>
#include <curses.h>

char *capitalize(char *string);
int get_length(char *T[]);
int get_length2(WINDOW *T[]);

#endif