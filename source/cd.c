#include "shell.h"

int shell_cd(char **args){
    if (args[1]==NULL){
        char *home = getenv("HOME");
    if (home == NULL){
        printf("Could not find home\n");
    return 1;
                    }

    // save the current directory into OLDPWD before changing, so cd - can return here later
    char cwd_before[1024];
    if (getcwd(cwd_before, sizeof(cwd_before)) != NULL){
    setenv("OLDPWD", cwd_before, 1);
               }

    // chdir to home, separate from the home==NULL check above so success and failure are handled correctly
    if(chdir(home)!=0){ //implement home here
        perror("chdir error");
    return 1;
                    }
    // chdir succeeded, so cd with no args should report success, not failure
    return 0;
                    }
            else{
                if (strcmp(args[1],"-h")==0){
                    printf("Usage: cd path/to/destination to change cwd to destination\n OR cd to change cwd to home\n");
                    return 0;
                }
                if (args[2] != NULL){
                    printf("Usage: cd path/to/destination to change cwd to destination\n OR cd to change cwd to home\n");
                    return 1;
                }
                else{
                    if (strcmp(args[1], "-") == 0)
                    {
                    const char *oldpwd = getenv("OLDPWD");
                    if (oldpwd == NULL)
                {
                    fprintf(stderr, "No previous directory found.\n");
                    return 1;
                                        }
                    if (chdir(oldpwd) != 0)
                {
                    perror("chdir");
                    return 1;
                                        }
                    // successfully changed to the previous directory, stop here so we don't fall through to chdir(args[1]) below, which would try to chdir into a folder literally named "-"
                    return 0;
                                        }
                    // save the current directory into OLDPWD before changing, so cd - can return here later
                char cwd_before2[1024];
                if (getcwd(cwd_before2, sizeof(cwd_before2)) != NULL){
                setenv("OLDPWD", cwd_before2, 1);
                                }
                if (chdir(args[1])!=0){
                perror("cseshell"); //need to print error
                return 1;
                                                        }
                                }
                            }
                return 0;
                }