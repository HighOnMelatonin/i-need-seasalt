#include "shell.h"
// #include "usage.h"
const char *builtin_commands[] = {
    "cd",       // Changes the current directory of the shell to the specified path. If no path is given, it defaults to the user's home directory.
    "help",     //  List all builtin commands in the shell
    "env",      // Lists all the environment variables currently set in the shell
    "setenv",   // Sets or modifies an environment variable for this shell session
    "unsetenv", // Removes an environment variable from the shell
    "clear"
};
/*** This is array of functions, with argument char ***/
int (*builtin_command_func[])(char **) = {
    &shell_cd,     // builtin_command_func[0]: cd
    &shell_help,   // builtin_command_func[1]: help
    &list_env,     // builtin_command_func[4]: env
    &setenv_var,   // builtin_command_func[5]: setenv
    &unsetenv_var, // builtin_command_func[6]: unsetenv
    &shell_clear
};

// The main function where the shell's execution begins
int main(void)
{
    // Define an array to hold the command and its arguments
    char *cmd[MAX_ARGS];
    int child_status;
    pid_t pid;
    type_prompt(); // Display the prompt

    for (int i = 0; i < MAX_ARGS; i++)
    {
        cmd[i] = NULL;
    }

    read_command(cmd); // Read a command from the user

    // empty command
    while (cmd[0] == NULL)
    {
        type_prompt();
        for (int i = 0; i < MAX_ARGS; i++)
        {
            cmd[i] = NULL;
        }
        read_command(cmd);
    }

    // If the command is "exit", break out of the loop to terminate the shell
    while (strcmp(cmd[0], "exit") != 0)
    {
        // usage
        //         if (strcmp(cmd[0], "usage") == 0)
        // {
        //     shell_usage(cmd);

        //     type_prompt();
        //     for (int i = 0; i < MAX_ARGS; i++){ cmd[i] = NULL;}
        //     read_command(cmd);

        //     while (cmd[0] == NULL)
        //     {
        //         type_prompt();
        //         for (int i = 0; i < MAX_ARGS; i++){ cmd[i] = NULL;}
        //         read_command(cmd);
        //     }

        //     continue;
        // }

        // Formulate the full path of the command to be executed
        char full_path[PATH_MAX];
        char cwd[1024];
        bool skipped = false;
        if (strcmp(cmd[0], "usage") == 0)
        {
            if (cmd[1] == NULL || cmd[2] != NULL)
            {
                skipped = true;
                printf("Usage: type usage <cmd> to get usage of command\n");
            }
            else
            {
                if (strcmp(cmd[1], "usage") == 0 || strcmp(cmd[1], "-h") == 0)
                {
                    skipped = true;
                    printf("Usage: type usage <cmd> to get usage of command\n");
                }
                else if (strcmp(cmd[1], "exit") == 0)
                {
                    skipped = true;
                    printf("Usage: type exit to terminate and exit the shell\n");
                }
                else
                {
                    cmd[0] = cmd[1];
                    cmd[1] = "-h";
                    cmd[2] = NULL;
                }
            }
        }
        if (skipped == false)
        {
            if (builtin_func_check(cmd) == -2)  // Not a built-in function
            {
                pid_t pid = fork();
                if (pid == 0)
                {
                    char path[PATH_MAX];
                    char full_path[PATH_MAX];

                    ssize_t len = readlink("/proc/self/exe", path, sizeof(path) - 1);
                    if (len != -1)
                    {
                        path[len] = '\0';
                        char *last_slash = strrchr(path, '/');
                        if (last_slash != NULL)
                        {
                            *last_slash = '\0';
                        }
                        snprintf(full_path, sizeof(full_path), "%s/bin/%s", path, cmd[0]);
                        execv(full_path, cmd);
                        // If execv returns, command execution has failed
                        printf("Command %s not found\n", cmd[0]);
                    }
                    else
                    {
                        perror("readlink failed");
                    }    
                }
            }
        }
        type_prompt();
        for (int i = 0; i < MAX_ARGS; i++)
        {
            cmd[i] = NULL;
        }
        read_command(cmd);
        while (cmd[0] == NULL)
        {
            type_prompt();
            for (int i = 0; i < MAX_ARGS; i++)
            {
                cmd[i] = NULL;
            }
            read_command(cmd);
        }
    }
    exit(0);
}

// Helper function to figure out how many builtin commands are supported by the shell
int num_builtin_functions()
{
    return (sizeof(builtin_commands) / sizeof(char *));
};

int builtin_func_check(char *args[])
{
    // Loop through our command list and check if the commands exist in the builtin command list
    for (int command_index = 0; command_index < num_builtin_functions(); command_index++)
    {
        if (strcmp(args[0], builtin_commands[command_index]) == 0) // Assume args[0] contains the first word of the command
        {
            // We will create new process to run the function with the specific command except for builtin commands.
            // These have to be done by the shell process.
            return (*builtin_command_func[command_index])(args);
        }
    }
    return -2;
}
