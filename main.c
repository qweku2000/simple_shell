#include "shell.h"

/**
 *main - main entry point for program
 *
 * return - void
*/

int main()
{
  while (1)
    {
      prompt_line();
    }
  return (0);

}


/**
 * prompt_line - Function to print prompt and read input from user
 */
void prompt_line()
{
    /* Initialization */
    char *buffer_original = NULL;
    char *string;
    char *buffer_copy;
    ssize_t getline_bytes;
    size_t n = 0;
    int no_tokens = 0, i;
    char **string_arr;
    char *token;
    char buf[1064];
    int interactive = isatty(fileno(stdin));

    if (interactive)
    {
        if (getcwd(buf, sizeof(buf)) != NULL)
        {
            write(STDOUT_FILENO, buf, strlen(buf));
	    write(STDOUT_FILENO, "\n$ ", 3);
        }
        else
        {
            perror("Error: cwd error");
        }
    }

    /* Function for reading input from user */
    getline_bytes = getline(&buffer_original, &n, stdin);
    if (getline_bytes == -1)
      {
	free(buffer_original); /*Free dynamically allocated buffer*/
	exit(0);
      }
    if (getline_bytes == 1 && buffer_original[0] == '\n')
      {
	free(buffer_original); /*Free dynamically allocated buffer*/
	return;
      }

    buffer_copy = strdup(buffer_original);
   
    hashes(buffer_copy);

    /* Tokenize string */
    string = strtok(buffer_original, " \n");

    if (string)
    {
        /* Keep adding up to keep track of the number of tokens needed */
        no_tokens++;
        string = strtok(NULL, " \n");
    }
    no_tokens++;

    string_arr = malloc(sizeof(char *) * (no_tokens + 1));

    token = strtok(buffer_copy, " \n");
    for (i = 0; token != NULL; i++)
    {
        string_arr[i] = strdup(token);
        token = strtok(NULL, " \n");
    }
    string_arr[i] = NULL;

    execute(string_arr);

    for (i = 0; string_arr[i] != NULL; i++)
    {
      free(string_arr[i]);
    }
    free(string_arr);
    free(buffer_copy);
    free(buffer_original);
}
