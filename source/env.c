// environment manager
// includes functions for viewing and editing the environment
#include "shell.h"

// Declaration of the external variable 'environ'
extern char** environ;

int list_env(char **args){
    // Print the environment variables
    if(args[1]!=NULL){
        printf("Usage: type env to print environemnt variables\n");
    if(strcmp(args[1],"-h")==0){
        return 0;
    }
    return 1;
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
    if(args[1]== NULL){
        printf("Usage: setenv KEY=VALUE to set environment variable KEY\n");
        return 1;
    }
    if(strcmp(args[1],"-h")==0){
        printf("Usage: setenv KEY=VALUE to set environment variable KEY\n");
        return 0;
    }
    char* end = strchr(args[1], '=');
    if (end == NULL){
        // there is no value assignment
        printf("Missing args: VALUE\n");
        printf("Usage: setenv KEY=VALUE\n");
        return 1;
    }
    else{
        printf("%s\n", args[1]);

        return putenv(args[1]);    // adds to environment variables, argument is in format name=value
    }
}

int unsetenv_var(char **args){
    /*
    Removes the environment variable
    */
    if(args[1]== NULL){
        printf("Usage: type unsetenv KEY to remove environment variable KEY\n");
        return 1;
    }
    if(strcmp(args[1],"-h")==0){
        printf("Usage: type unsetenv KEY to remove environment variable KEY\n");
        return 0;
    }
    return unsetenv(args[1]);
}