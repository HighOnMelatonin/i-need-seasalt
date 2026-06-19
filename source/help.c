#include "shell.h"
#include <sys/types.h>
#include <dirent.h>
int shell_help(char **args){
    if(args[1]!=NULL){
        printf("Usage: type help to list all commands\n");
    if(strcmp(args[1],"-h")==0){
        return 0;
    }
    return 1;
    }
    printf("Built in Functions:\n");
    printf("- usage\n");
    printf("- exit\n");
    for(int i = 0; i<num_builtin_functions();i++){
        printf("- %s\n",builtin_commands[i]);
    }
    printf("System Programs:\n");

    char path[1024];
    char bin_path[1024];
    ssize_t len = readlink("/proc/self/exe", path, sizeof(path) - 1);
    
    if (len == -1) {
        perror("readlink failed");
        return 1;
    }

    path[len] = '\0';
    char *last_slash = strrchr(path, '/');
    if (last_slash != NULL) {
        *last_slash = '\0';
    }
    snprintf(bin_path, sizeof(bin_path), "%s/bin", path);

    DIR *d = opendir(bin_path);
    if (!d) {
        perror("Failed to open bin directory");
        return 1;
    }

    struct dirent *dir;
    while ((dir = readdir(d)) != NULL) {
        // Skip hidden files (dotfiles)
        if (dir->d_name[0] != '.') {
            printf("- %s\n", dir->d_name);
        }
    }
    closedir(d);

    return 0;

}