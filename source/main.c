#include "shell.h"
// #include "usage.h"
#include <stdbool.h>
#include "resource_usage.h"
#include <signal.h>

const char *builtin_commands[] = {
    "cd",       // Changes the current directory of the shell to the specified path. If no path is given, it defaults to the user's home directory.
    "help",     //  List all builtin commands in the shell
    "env",      // Lists all the environment variables currently set in the shell
    "setenv",   // Sets or modifies an environment variable for this shell session
    "unsetenv", // Removes an environment variable from the shell
    "clear",
    "setcolor"};
/*** This is array of functions, with argument char ***/
int (*builtin_command_func[])(char **) = {
    &shell_cd,     // builtin_command_func[0]: cd
    &shell_help,   // builtin_command_func[1]: help
    &list_env,     // builtin_command_func[4]: env
    &setenv_var,   // builtin_command_func[5]: setenv
    &unsetenv_var, // builtin_command_func[6]: unsetenv
    &shell_clear,
    &shell_setcolor
    };


void auto_path(){
    char path[PATH_MAX];
    char PATHSET[PATH_MAX+9];

    ssize_t len = readlink("/proc/self/exe", path, sizeof(path) - 1);
    if (len != -1)
    {
        path[len] = '\0';
        char *last_slash = strrchr(path, '/');
        if (last_slash != NULL)
        {
            *last_slash = '\0';
        }
        snprintf(PATHSET, sizeof(PATHSET), "CSE_PATH=%s/bin", path);
        putenv(PATHSET);
        
    }
    else
    {
        perror("readlink failed");
    }
}

int read_rc(){
    int child_status;
    char *cmd[MAX_ARGS];
    pid_t pid;
    char path[PATH_MAX];
    int exit_code;
    char PATHSET[PATH_MAX];

    ssize_t len = readlink("/proc/self/exe", path, sizeof(path) - 1);
    if (len != -1)
    {
        path[len] = '\0';
        char *last_slash = strrchr(path, '/');
        if (last_slash != NULL)
        {
            *last_slash = '\0';
        }
        snprintf(PATHSET, sizeof(PATHSET), "%s/.cseshellrc", path);        
    }

    FILE *pipe = fopen(PATHSET, "r");
    if (pipe == NULL) {
        perror("popen");
        return 1;
    }
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {

        buffer[strcspn(buffer, "\n")] = '\0';
        if (buffer[0] == '\0' || buffer[0] == '#') {
            continue;
        }
        for (int i = 0; i < MAX_ARGS; i++) {
            cmd[i] = NULL;
        }

        int idx = 0;
        char *space_thing = strtok(buffer, " \t");
        while (space_thing != NULL && idx < MAX_ARGS - 1) {
            cmd[idx] = space_thing;
            idx++;
            space_thing = strtok(NULL, " \t");
        }
        if(cmd[0]==NULL){
            continue;
        }
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
            int check_result = builtin_func_check_lookup(cmd[0]);
            if (check_result == -2)   // Not a built-in function
            {
                pid_t pid = fork();
                if (pid == 0)
                {
                    char *cse_path = getenv("CSE_PATH");
                    char *cse_path_copy = strdup(cse_path);
                    char *part_path = strtok(cse_path_copy,":");

                    while (part_path!=NULL){
                        char full_path[PATH_MAX];
                        snprintf(full_path,sizeof(full_path),"%s/%s",part_path,cmd[0]);
                        execv(full_path, cmd);
                        part_path = strtok(NULL,":");
                    }
                    free(cse_path_copy);

                    printf("Command %s not found\n", cmd[0]);
                    _exit(1);
                }
                waitpid(pid, &child_status, 0);
            }
            else
            {
                run_builtin(check_result, cmd);   // it IS a builtin — actually run it
            }
        }
    }
    
    fclose(pipe);
    // printf("Live daemons: %d\n", daemon_count);
    return 0;
}


void sigintHandler(int sig_num){
    /*
    To catch signal interrupts(ctrl + c)

    https://en.cppreference.com/c/program/SIG_types
    */
    signal(SIGINT, sigintHandler);
    printf("Type \"exit\" to exit the shell");
    fflush(stdout);
}

// The main function where the shell's execution begins
int main(void)
{
    auto_path();
    read_rc();
    // Define an array to hold the command and its arguments
    char *cmd[MAX_ARGS];
    int child_status;
    // pid_t pid;
    signal(SIGINT, sigintHandler);
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
        // for (int i = 0; i < MAX_ARGS; i++)
        // {
        //     cmd[i] = NULL;
        // }
        read_command(cmd);
    }

    // If the command is "exit", break out of the loop to terminate the shell
    while (strcmp(cmd[0], "exit") != 0)
    {
        //resource usage 
       struct rusage before_usage;
        struct rusage after_usage;
        bool is_builtin = false;

        


        // Formulate the full path of the command to be executed
        // char full_path[PATH_MAX];
        // char cwd[1024];
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

        char original_command[MAX_LINE];
        snprintf(original_command, sizeof(original_command), "%s", cmd[0]);


        if (skipped == false)
        {
            int check_result = builtin_func_check_lookup(cmd[0]);  // see Step 2 — just checks, doesn't run yet
            is_builtin = (check_result != -2);

            get_resource_snapshot(&before_usage, is_builtin);

            if (check_result == -2)   // Not a built-in function
            {
                pid_t pid = fork();
                if (pid == 0)
                {
                    char *cse_path = getenv("CSE_PATH");
                    char *cse_path_copy = strdup(cse_path);
                    char *part_path = strtok(cse_path_copy,":");

                    while (part_path!=NULL){
                        char full_path[PATH_MAX];
                        snprintf(full_path,sizeof(full_path),"%s/%s",part_path,cmd[0]);
                        execv(full_path, cmd);
                        part_path = strtok(NULL,":");
                    }
                    free(cse_path_copy);

                    printf("Command %s not found\n", cmd[0]);
                    return 1;
                }
                waitpid(pid, &child_status, 0);
            }
            else
            {
                run_builtin(check_result, cmd);   // it IS a builtin — actually run it
            }
        

        get_resource_snapshot(&after_usage, is_builtin);
        print_resource_usage(original_command, before_usage, after_usage);

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

// Returns the index of the builtin if found, or -2 if not a builtin. Does NOT run it.
int builtin_func_check_lookup(char *cmd0)
{
    for (int command_index = 0; command_index < num_builtin_functions(); command_index++)
    {
        if (strcmp(cmd0, builtin_commands[command_index]) == 0)
        {
            return command_index;
        }
    }
    return -2;
}

// Runs the builtin at the given index.
int run_builtin(int index, char *args[])
{
    return (*builtin_command_func[index])(args);
}