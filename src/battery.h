#ifndef __BATTERY_H__
#define __BATTERY_H__

#ifdef __unix__
// #define READ_SRC "/proc/acpi/battery/"
// #define READ_SRC "/sys/class/power_supply/%s/uevent"
#define READ_SRC "/sys/class/power_supply/BAT1/uevent"
// #elif __APPLE__
// #define READ_SRC "/proc/acpi/battery/"
// #elif _WIN64
// #define READ_SRC "/proc/acpi/battery/"
#endif

typedef enum battery_state
{
    AC_CHARGING,
    AC_CHARGED,
    AC_ON_BATTERY,
    AC_INVALID,
} battery_state;

// typedef const struct factory_info
// {

// } factory_info;

typedef struct battery_status
{
    unsigned short battery;
    long uptime;
    // factory_info man_inf;
    char name[32];
    char manufacturer[32];
    char model_name[32];
    char serial_no[32];
    // battery_state state;
    char state[32];
} battery_status;

void scrape_battery_info(battery_status *status);
void update_status();

#endif