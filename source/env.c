// environment manager
// includes functions for viewing and editing the environment
#include <stdio.h>
#include <stdlib.h>

// Declaration of the external variable 'environ'
extern char** environ;

int env(){
    // Print the environment variables
    char** env = environ;   // Pointer to the array of environment strings

    while (*env) {
        printf("%s\n", *env);
        env++;
    }
    
    return 0;
}

int setenv(char **args){
    /*
    Sets environment variable

    Usage:
    $$ setenv KEY=VALUE

    No output
    */
    char* end = strchr(args[1], '=');
    if (end == "NULL"){
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

int unsetenv(char **args){
    /*
    Removes the environment variable
    */
    return unsetenv(args[1]);
}