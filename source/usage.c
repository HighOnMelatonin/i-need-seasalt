#include <stdio.h>
#include <string.h>
#include "usage.h"


//usage
int shell_usage(char **args)
{
    if (args[1] == NULL)
    {
        printf("Command not given. Type usage <command>.\n");
        return 1;
    }

    if (strcmp(args[1], "cd") == 0)
        printf("Type: cd <directory> to change the current working directory.\n");

    else if (strcmp(args[1], "help") == 0)
        printf("Type: help to list all builtin commands.\n");

    else if (strcmp(args[1], "exit") == 0)
        printf("Type: exit to terminate the shell.\n");

    else if (strcmp(args[1], "usage") == 0)
        printf("Type: usage <command> to see how to use a builtin command.\n");

    else if (strcmp(args[1], "env") == 0)
        printf("Type: env to list all environment variables.\n");

    else if (strcmp(args[1], "setenv") == 0)
        printf("Type: setenv <ENV> <VALUE> to set an environment variable.\n");

    else if (strcmp(args[1], "unsetenv") == 0)
        printf("Type: unsetenv <ENV> to remove an environment variable.\n");

    else
        printf("The command you gave: %s, is not part of CSEShell's builtin command.\n", args[1]);

    return 1;
}
