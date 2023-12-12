#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

#define BUFFER_SIZE 4096
#define MAX_INPUT_SIZE 1024

extern char **environ;

void hashes(char *input);
void replace_hashtags(char *str);
void prompt_line();
void execute(char *argv[]);
char* environment(char* env);
int exit_shell();
int dir_change(char* argv);
void env_var();
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void _unsetenv(char *var);
void _setenv(char *var,char* val);
int _getchar();


#endif
