// Code for shell history
#include "shell.h"
#include <stdio.h>

int get_history(){
    // Function to get history
    FILE *file = fopen("~/.ss_history", "r");
    if (file == NULL){
        perror("Failed to open history");
        return EXIT_FAILURE;
    }


    fclose(file);
    return 0;
}

int add_history(char **args){
    // Function to add cmd to history
    // "a" appends to file
    FILE *file = fopen(".ss_history", "a");
    if (file == NULL){
        perror("Failed to open history");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < MAX_ARGS; i++){
        fprintf(file, args[i]);
    }

    fclose(file);
    return 0;
}

// Function to delete all shell history
int clear_history(){
    // Function to delete all entries
    // "w" overwrites the file, clearing history
    FILE *file = fopen(".ss_history", "w");
    if (file == NULL){
        perror("Failed to open history");
        return EXIT_FAILURE;
    }

    // clear history
    fprintf(file, "");
    fclose(file);
    return 0;
}