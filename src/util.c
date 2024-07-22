#include "util.h"

char *capitalize(char *string)
{
  for (int i = 0; i < strlen(string); i++)
    string[i] = toupper(string[i]);
  return string;
}

int get_length(char *T[])
{
  int plus = 0;
  int total = 0;
  while(*(T + plus) != NULL)
  {
    plus++;
    total++;
  }
  return total;
}

int get_length2(WINDOW *T[])
{
  int plus = 0;
  int total = 0;
  while(*(T + plus) != NULL)
  {
    plus++;
    total++;
  }
  return total;
}