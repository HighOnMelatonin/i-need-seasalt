#include "shell.h"

int shell_cd(char **args){
    if (args[1]==NULL){
                char *home = getenv("HOME");
                if (home == NULL){
                    printf("Could not find home");
                    return 1;
                }
                else if(chdir(home)!=0){ //implement home here
                    perror("chdir error");}
                    return 1;
                }
            else{
                if (strcmp(args[1],"-h")==0){
                    printf("Usage: cd path/to/destination to change cwd to destiantion\n OR cd to change cwd to home");
                    return 0;
                }
                if (args[2] != NULL){
                    printf("Usage: cd path/to/destination to change cwd to destiantion\n OR cd to change cwd to home");
                    return 1;
                }
                else{
                    if (chdir(args[1])!=0){
                        perror("cseshell"); //need to print error
                        return 1;
                    }
                }
            }
    return 0;
}