typedef enum battery_state
{
    AC_CHARGING,
    AC_CHARGED,
    AC_ON_BATTERY,
    AC_INVALID
} battery_state;

typedef const struct factory_info
{

} factory_info;

typedef struct battery_status
{
    unsigned short battery;
    long uptime;
    battery_state state;
} battery_status;

#ifdef __unix__
// #define READ_SRC "/proc/acpi/battery/"
#define READ_SRC "/sys/class/power_supply/"
// #elif __APPLE__
// #define READ_SRC "/proc/acpi/battery/"
// #elif _WIN64
// #define READ_SRC "/proc/acpi/battery/"
#endif

static void scrape_battery_info();
static void update_status();