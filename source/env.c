// environment manager
// includes functions for viewing and editing the environment
#include "shell.h"

// Declaration of the external variable 'environ'
extern char** environ;

int list_env(char **args){
    // Print the environment variables
    if(strcmp(args[1],"-h")==0){
        printf("Usage: type env to print environemnt variables");
        return 0;
    }
    char** env = environ;   // Pointer to the array of environment strings

    while (*env) {
        printf("%s\n", *env);
        env++;
    }
    
    return 0;
}

int setenv_var(char **args){
    /*
    Sets environment variable

    Usage:
    $$ setenv KEY=VALUE

    No output
    */
    if(strcmp(args[1],"-h")==0){
        printf("Usage: setenv KEY=VALUE to set environment variable KEY");
        return 0;
    }
    char* end = strchr(args[1], '=');
    if (end == NULL){
        // there is no value assignment
        printf("Missing args: VALUE");
        printf("Usage: setenv KEY=VALUE");
        return 1;
    }
    else{
        printf(args[1]);

        return putenv(args[1]);    // adds to environment variables, argument is in format name=value
    }
}

int unsetenv_var(char **args){
    /*
    Removes the environment variable
    */
    if(strcmp(args[1],"-h")==0){
        printf("Usage: type unsetenv KEY to remove environment variable KEY");
        return 0;
    }
    return unsetenv(args[1]);
}