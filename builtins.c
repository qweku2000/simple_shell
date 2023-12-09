#include "shell.h"

/**
 * exit_shell - Exits the shell program
 * @status: The exit status code
 *
 * Return: Always returns 0
 */
int exit_shell(char *status)
{
  int code = 0;

  if (status != NULL)
  {
    code = atoi(status);
  }
  exit(code);
  return (0);
}


/**
 * dir_change - Changes the current working directory
 * @argv: The directory to change to
 *
 * Return: 0 on success, -1 on failure
 */
int dir_change(char argv[])
{
    if (chdir(argv) < 0)
    {
       printf("cd failed\n");
       return (-1);
    }
    else
    {
       prompt_line();
       return (0);
    }
}

/**
 * environment_variables - Prints the environmental variables
 *
 * This function prints the list of environmental variables
 * in the current environment.
 */
void env_var(void)
{
    int i;
    char **env = environ;

    for (i = 0; env[i] != NULL; i++)
    {
      printf("%s\n", env[i]);
    }
}
