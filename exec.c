#include "shell.h"


/**
 * executable - Executes the given command
 * @argv: Array of arguments passed to the command
 */
void execute(char *argv[])
{
    char *cmd = NULL;
    char *cmd_act = NULL;

    
    if (argv)
    {
        /* Command is assigned to the first string in argv */
        cmd = argv[0];

      
       if (strcmp(cmd, "exit") == 0)
	  {
            exit_shell(argv[1]);
	  }
        else if (strcmp(cmd, "cd") == 0)
	  {
            /* Change directory using chdir function */
	    
            if (!argv[1])
	      {
                char *home_dir = getenv("HOME");
                if (home_dir)
		  {
                    if (chdir(home_dir) != 0)
		      {
                        perror("Error: chdir failed");
		      }
		  }
                else
		  {
                    printf("Error: HOME environment variable not set\n");
		  }
	      }
            else if (chdir(argv[1]) != 0)
	      {
                perror("Error: chdir failed");
	      }
	  }
        else if (strcmp(cmd, "env") == 0)
	  {
            env_var();
	  }
	else if ( strcmp(cmd,"$?") == 0)
	  {
	    
	  }
        else
	  {
            /* Execute external command */

            /* Create a child process */
            pid_t pid = fork();

            if (pid < 0)
	      {
                perror("Error: Fork failed");
	      }
            else if (pid == 0)
	      {
                /* Child process */

                /* Make sure that the new command is now a full path of the command */
                cmd_act = environment(cmd);


                if (cmd_act != NULL)
		  {
		    if (execve(cmd_act, argv, NULL) < 0)
		      {
			perror("Error:");
			free(cmd_act); /*Free dynamically allocated cmd_act*/
			exit(EXIT_SUCCESS);
		      }
		  }
                else
		  {
                    printf("%s: 1: %s: not found\n", argv[0], cmd);
                    free(cmd_act); /* Free dynamically allocated cmd_act*/
                    exit(EXIT_SUCCESS);
		  }
	      }
            else
	      {
                /* Parent process */

                /* Wait for the child process to finish */
                int status;
                waitpid(pid, &status, 0);
	      }
	  }
    }
    
    free(cmd_act); /*Free dynamically allocated cmd_act (if not NULL)*/
}
