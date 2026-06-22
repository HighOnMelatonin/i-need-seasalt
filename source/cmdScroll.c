// Code for shell history
#include "shell.h"
#include <stdio.h>

int get_history(char **args){
    // Function to get history
    if (args[0] == NULL){
        char *username = getlogin();
        if(username==NULL){
            printf("User Home directory not found");
            return 0;
        }
        char historypath[PATH_MAX];
        snprintf(historypath,sizeof(historypath),"/home/%s/.ss_history",username);
        FILE *file = fopen(historypath, "r");
        if (file == NULL){
            perror("Failed to open history");
            return EXIT_FAILURE;
        }

        char line[MAX_ARGS];
        while (fgets(line, sizeof(line), file) != NULL){
            printf("%s", line);
        }

        fclose(file);
        return 1;
    }
    else{
        if (strcmp(args[1], "-h") == 0){
            printf("Usage: history, to get the history of the commands during this session");
            return 0;
        }
    return 1;
    }
}

int add_history(char **args){
    // Function to add cmd to history
    // "a" appends to file
    if (args[0] == NULL){
        // If no arguments given, fail
        return 1;    
    }
    else if (args[1] != NULL){
        // if more than 1 arguments given, fail
        return 1;
    }
    else{
        char *username = getlogin();
            if(username==NULL){
                printf("User Home directory not found");
                return 1;
            }
            char historypath[PATH_MAX];
            snprintf(historypath,sizeof(historypath),"/home/%s/.ss_history",username);
        FILE *file = fopen(historypath, "a");
        if (file == NULL){
            perror("Failed to open history");
            return EXIT_FAILURE;
        }

        fprintf(file, "%s\n", *args);

        fclose(file);
        return 0;
    }
}

// Function to delete all shell history
int clear_history(){
    // Function to delete all entries
    // "w" overwrites the file, clearing history
    char *username = getlogin();
        if(username==NULL){
            printf("User Home directory not found");
            return 1;
        }
        char historypath[PATH_MAX];
        snprintf(historypath,sizeof(historypath),"/home/%s/.ss_history",username);
    FILE *file = fopen(historypath, "w");
    if (file == NULL){
        perror("Failed to open history");
        return EXIT_FAILURE;
    }

    // clear history
    fprintf(file, "");
    fclose(file);
    return 0;
}
