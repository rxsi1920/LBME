#include "battery.h"
#include "util.h"

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void place_split_value(char *tok, char *split, const char *place)
{
  capitalize(tok = strtok(NULL, split));
  tok[strlen(tok) - 1] = 0;
  if (tok[0] == '\0')
    tok = "UNKNOWN";
  sprintf((char*)place, "%s", tok);
}

void scrape_battery_man_info(battery_status *status)
{
  FILE *fptr;
  if ((fptr = fopen(READ_SRC, "r")) != NULL)
  {
    char line[1024];
    char *split = "=";
    char *token;
    unsigned short filled;
    unsigned short full;
    while (fgets(line, sizeof(line), fptr))
    {
      token = strtok(line, split);
      if (strcmp(token, "POWER_SUPPLY_NAME") == 0)
        place_split_value(token, split, status->man_inf.name);
      else if (strcmp(token, "POWER_SUPPLY_MODEL_NAME") == 0)
        place_split_value(token, split, status->man_inf.model_name);
      else if (strcmp(token, "POWER_SUPPLY_MANUFACTURER") == 0)
        place_split_value(token, split, status->man_inf.manufacturer);
    }
    fclose(fptr);
  }  
}

void scrape_battery_info(battery_status *status)
{
  FILE *fptr;
  if ((fptr = fopen(READ_SRC, "r")) != NULL)
  {
    char line[1024];
    char *split = "=";
    char *token;
    unsigned short filled;
    unsigned short full;
    while (fgets(line, sizeof(line), fptr))
    {
      token = strtok(line, split);
      if (strcmp(token, "POWER_SUPPLY_STATUS") == 0)
        place_split_value(token, split, status->state);
      else if (strcmp(token, "POWER_SUPPLY_ENERGY_FULL") == 0)
      {
        token = strtok(NULL, split);
        token[strlen(token) - 1] = 0;
        if (token[0] == '\0')
          token = 0;
        full = (unsigned short)atoi(token);
      }
      else if (strcmp(token, "POWER_SUPPLY_ENERGY_NOW") == 0)
      {
        token = strtok(NULL, split);
        token[strlen(token) - 1] = 0;
        if (token[0] == '\0')
          token = 0;
        filled = (unsigned short)atoi(token);
        if (full == 0)
          status->battery = 0;
        else
          status->battery = (unsigned short)floor(filled * 100 / full);
      }
    }
    fclose(fptr);
  }

  if ((fptr = fopen(READ_UPTIME_SRC, "r")) != NULL)
  {
    char line[64];
    char *token;
    char *split = " ";
    fgets(line, sizeof line, fptr);
    token = strtok(line, split);
    long int uptime = ceil(atof(token));
    status->uptime_h = uptime / 3600;
    status->uptime_m = (uptime % 3600) / 60;
    status->uptime_s = uptime % 60;
  }
}

void update_status()
{
}