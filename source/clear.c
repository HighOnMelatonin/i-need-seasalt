#include "shell.h"

int shell_clear(char **args){
    if(strcmp(args[1],"-h")==0){
        printf("Usage: type clear to clear screen\n");
        return 0;
    }
    #ifdef _WIN32
        system("cls"); // Windows command to clear screen
    #else
        system("clear"); // UNIX/Linux command to clear screen
    #endif
    return 0;
}