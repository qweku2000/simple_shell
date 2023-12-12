#include "shell.h"

/**
 * environment - Retrieves the full path of a command from the environment variables
 * @env: The command to search for
 *
 * Return: The full path of the command if found, NULL otherwise
 */
char *environment(char *env)
{
    char *cmd_path = getenv("PATH");
    char *copied_path;
    char *paths;
    char *full_path = NULL;
    struct stat path_info;
    int env_length, paths_length;

    if (cmd_path)
    {
        copied_path = strdup(cmd_path);
        env_length = strlen(env);
        paths = strtok(copied_path, ":");
        while (paths)
        {
            paths_length = strlen(paths);
            full_path = malloc(env_length + paths_length + 2);
            if (full_path)
            {
                strcpy(full_path, paths);
                strcat(full_path, "/");
                strcat(full_path, env);

                if (stat(full_path, &path_info) == 0)
                {
                    free(copied_path);
                    return full_path;
                }
                else
                {
                    free(full_path);
                    paths = strtok(NULL, ":");
                }
            }
        }
        free(copied_path);
        if (stat(env, &path_info) == 0)
        {
            return env;
        }
    }

    return NULL;
}
