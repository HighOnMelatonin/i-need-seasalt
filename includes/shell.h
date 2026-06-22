#ifndef SHELL_H
#define SHELL_H

#include <limits.h> // For PATH_MAX
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


#define MAX_LINE 1024
#define MAX_ARGS 64
#define BIN_PATH "./bin/"

void type_prompt();
void read_command(char **cmd);

/*
Handler of each shell builtin function
*/
extern int (*builtin_command_func[])(char **);
extern const char *builtin_commands[];
/*
Handler of each shell builtin function
*/
int shell_cd(char **args);
int shell_help(char **args);
int list_env(char **args);
int setenv_var(char **args);
int unsetenv_var(char **args);
int shell_clear(char **args);
int shell_setcolor(char **args);
int num_builtin_functions();
int builtin_func_check(char *args[]);
int builtin_func_check_lookup(char *cmd0);
int run_builtin(int index, char *args[]);
int clear_history();
int add_history(char **args);
int get_history();

extern char *current_color;

#endif