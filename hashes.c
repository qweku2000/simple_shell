#include "shell.h"

/**
 * hashtags - handle comments
 * @buff: user input;
 * Return:void
 */
void hashes(char *input)
{
  int i;

  for (i = 0; input[i] != '\0'; i++)
    {
      if (input[i] == '#')
        {
          input[i] = '\0';
          return;
        }
    }
}
