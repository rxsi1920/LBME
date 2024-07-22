#ifndef __LBME_H__
#define __LBME_H__

#include "app_info.h"
#include "pages.h"
#include "screen.h"

int run(int argc, char **argv);
int parse_args(int argc, char **argv);
void print_help_table();
void print_usage(int argc, char **argv);
void print_version();

#endif