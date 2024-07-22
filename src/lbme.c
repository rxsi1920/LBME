#include "lbme.h"

#include <getopt.h>
#include <ncurses.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

volatile sig_atomic_t prog_cms = 0;

const char *short_opts = "::hpuv";

const struct option long_opts[] = {
    {"help", no_argument, 0, 'h'},
    {"pquick", no_argument, 0, 'p'},
    {"update", no_argument, 0, 'u'},
    {"version", no_argument, 0, 'v'},
};

int run(int argc, char **argv)
{
  int c = parse_args(argc, argv);
  make_screen();
  while (prog_cms != -1)
  {
    draw_battery_info();
    if (settings_open)
      draw_settings_page();
    else
      draw_home_page();
  }
  close_screen();
}

int parse_args(int argc, char **argv)
{
  int c;
  while ((c = getopt_long(argc, argv, short_opts, long_opts, 0)) != -1)
  {
    switch (c)
    {
    case 'h':
      print_help_table();
      exit(0);
      break;
    case 'p':
      exit(0);
      break;
    case 'v':
      print_version();
      exit(0);
      break;
    default:
      print_usage(argc, argv);
      exit(0);
      break;
    }
  }
  return c;
}

void print_help_table()
{
  print_version();
  printf(
      "Usage: lbme -[flag]\n"
      "   or: lbme --[long_flag]\n"
      "\n"
      "Flags\n"
      " -h, --help         Show help screen\n"
      " -p, --pquick       Quick print the battery info\n"
      " -u, --upgrade      Upgrade to latest git release\n"
      " -v, --version      Display package version\n");
}

void print_usage(int argc, char **argv)
{
  print_version();
  printf("Unknown combination of arguments:");
  for (int i = 1; i < argc; i++)
    printf(" %s,", argv[i]);
  puts("\n");
  printf(
      "Usage: lbme -[flag]\n"
      "   or: lbme --[long_flag]\n\n"
      "Run with flags -h or --help to view list of available options\n");
}

void print_version() { printf("LBMe - Local Battery Meter (ver " LBME_VERSION ")\n"); }