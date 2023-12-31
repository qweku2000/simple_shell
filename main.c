#include "shell.h"

int main()
{
    while (1)
      {
        prompt_line();
      }
    return 0;
}

void prompt_line() {
    char *buffer_original = NULL;
    char *buffer_copy = NULL;
    ssize_t getline_bytes;
    size_t n = 0;
    char **commands = NULL;
    int i,j,num_commands;
    char* command = NULL;
    /* Print prompt */
    if (isatty(fileno(stdin)))
      {
        char buf[1064];
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

    /* Read input from user */
    getline_bytes = getline(&buffer_original, &n, stdin);
    if (getline_bytes == -1)
      {
        free(buffer_original);
        exit(0);
      }
    if (getline_bytes == 1 && buffer_original[0] == '\n')
      {
        free(buffer_original);
        return;
      }

    buffer_copy = strdup(buffer_original);
    hashes(buffer_copy);
    
    /* Tokenize string based on ; */
    command = strtok(buffer_original, ";\n");
    num_commands = 0;
    
    while (command != NULL)
      {
        commands = realloc(commands, (num_commands + 1) * sizeof(char *));
        commands[num_commands] = strdup(command);
        num_commands++;
        command = strtok(NULL, ";\n");
      }
    
    /* Execute each command */
    for (i = 0; i < num_commands; i++)
      {
        char **string_arr = NULL;
        int no_tokens = 0;
	
        /* Tokenize each command based on space */
        char *token = strtok(commands[i], " \n");
        while (token != NULL)
	  {
            string_arr = realloc(string_arr, (no_tokens + 1) * sizeof(char *));
            string_arr[no_tokens] = strdup(token);
            no_tokens++;
            token = strtok(NULL, " \n");
	  }

        /* Execute the command */
        string_arr = realloc(string_arr, (no_tokens + 1) * sizeof(char *));
        string_arr[no_tokens] = NULL;  /*Null-terminate the array*/
        execute(string_arr);

        /* Free memory */
        for (j = 0; j <= no_tokens; j++)
	  {
            free(string_arr[j]);
	  }
        free(string_arr);
    }

    /* Free memory */
    for (i = 0; i < num_commands; i++)
      {
        free(commands[i]);
      }
    free(commands);
    free(buffer_copy);
    free(buffer_original);
}
