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
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            snprintf(full_path, sizeof(full_path), "%s/bin/%s", cwd, cmd[0]);
        }
        else
        {
            perror("readlink failed");
            exit(1);
        }
        if (strcmp(cmd[0], "env") == 0){
            printf("%s \n",cmd[0]);
        }
        else if (strcmp(cmd[0], "setenv") == 0){
            // set environment

            printf("%s \n", cmd[1]);
        }
        else{
            printf("Command %s does not exist\n", cmd[0]);
        }

        for (int i = 0; cmd[i] != NULL; i++){
            free(cmd[i]);
        }
        execv(full_path, cmd);

        type_prompt();
        read_command(cmd);

    }
    
    exit(0);
}