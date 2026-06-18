// environment manager
// includes functions for viewing and editing the environment
#include <stdio.h>

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

int setenv(){
    /*
    Sets environment variable

    Usage:
    $$ setenv KEY=VALUE

    No output
    */
    
    return 0;
}