#ifndef __BATTERY_H__
#define __BATTERY_H__

#ifdef __unix__
// #define READ_SRC "/proc/acpi/battery/"
// #define READ_SRC "/sys/class/power_supply/%s/uevent"
#define READ_SRC "/sys/class/power_supply/BAT1/uevent"
#define READ_UPTIME_SRC "/proc/uptime"
// #elif __APPLE__
// #define READ_SRC "/proc/acpi/battery/"
// #elif _WIN64
// #define READ_SRC "/proc/acpi/battery/"
#endif

typedef const struct factory_info
{
  const char name[32];
  const char manufacturer[32];
  const char model_name[32];
  const char serial_no[32];
} factory_info;

typedef struct battery_status
{
  unsigned short battery;
  long uptime_h;
  int uptime_m;
  int uptime_s;
  factory_info man_inf;
  // battery_state state;
  char state[32];
} battery_status;

void scrape_battery_man_info(battery_status *status);
void scrape_battery_info(battery_status *status);
void update_status();

#endif