#include "shell.h"
// #include "builtins.h"

// The main function where the shell's execution begins
int main(void)
{
    // Define an array to hold the command and its arguments
    char *cmd[MAX_ARGS];
    int child_status;
    pid_t pid;

    printf(cmd[0]);

    type_prompt();     // Display the prompt
    read_command(cmd); // Read a command from the user

    // If the command is "exit", break out of the loop to terminate the shell
    while (strcmp(cmd[0], "exit") != 0){
        // Formulate the full path of the command to be executed
        char full_path[PATH_MAX];
        char cwd[1024];
        if (strcmp(cmd[0],"cd") == 0){
            if (cmd[1]==NULL){
                char *home = getenv("HOME");
                if (home == NULL){
                    printf("Could not find home");
                }
                else if(chdir(home)!=0){ //implement home here
                    perror("chdir error");}
                }
            else{
                if (cmd[2] != NULL){
                    printf("Usage: cd path/to/destination");
                }
                else{
                    if (chdir(cmd[1])!=0){
                        perror("cseshell"); //need to print error
                    }
                }
            }
        }
        else {
        char path[PATH_MAX];
        char full_path[PATH_MAX];

        ssize_t len = readlink("/proc/self/exe", path, sizeof(path) - 1);
        if (len != -1) {
            path[len] = '\0';
            char *last_slash = strrchr(path, '/');
            if (last_slash != NULL) {
                *last_slash = '\0';}
            snprintf(full_path, sizeof(full_path), "%s/bin/%s", path, cmd[0]);
            execv(full_path, cmd);
            // If execv returns, command execution has failed
            printf("Command %s not found\n", cmd[0]);   
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            snprintf(full_path, sizeof(full_path), "%s/bin/%s", cwd, cmd[0]);
        }
        else
        {
            perror("readlink failed");
        } 
    }
        

        type_prompt();
        read_command(cmd);

    }
    
    exit(0);
}