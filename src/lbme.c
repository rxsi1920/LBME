#include "app_info.h"
#include "lbme.h"
#include "screen.h"

#include <getopt.h>
#include <ncurses.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static volatile sig_atomic_t prog_cms = 0;

char *short_opts = "::hpuv";

static struct option long_opts[] = {
    {"help", no_argument, 0, 'h'},
    {"pquick", no_argument, 0, 'p'},
    {"update", no_argument, 0, 'u'},
    {"version", no_argument, 0, 'v'},
};

int run(int argc, char **argv)
{
    int c = parse_args(argc, argv);
    make_screen();
    while(prog_cms != -1)
    {
        handle_keypress(getch());
        refresh();
    }
    close_screen();
}

static int parse_args(int argc, char **argv)
{
    int c;
    while ((c = getopt_long(argc, argv, short_opts, long_opts, 0)) != -1)
    {
        switch (c)
        {
        case 'h':
            print_help_table();
            break;
        case 'p':
            break;
        case 'v':
            print_version();
            exit(0);
            break;
        default:
            print_usage();
            break;
        }
    }
    return c;
}

static void print_help_table()
{
    print_version();
    printf(
        "Usage: lbme -[flag]\n"
        "\n"
        "Flags\n"
        " -h, --help         Show help screen\n"
        " -p, --pquick       Ouput battery info\n"
        " -u, --upgrade      Upgrade to latest git release\n"
        " -v, --version      Display package version\n");
    exit(0);
}

static void print_usage()
{
    print_version();
    printf(
        "Usage: lbme -[flag]\n"
        "\n"
        "Run with flags -h or --help to view list of available options\n"
        "\n");
    exit(0);
}

static void print_version()
{
    printf(
        "LBMe - Local Battery Meter (ver " LBME_VERSION ") [" SOURCE_VERSION "]\n"
        "\n");
}

static void handle_keypress(int key)
{
    switch (key)
    {
    case 'a':
        break;
    case 'b':
        break;
    case 't':
        break;
    default:
        break;
    }
}