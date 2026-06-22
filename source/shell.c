// This code was written by ChatGPT4
// Modify it for your own usage to implement features for PA1 (or completely
// rewrite it) Include the shell header file for necessary constants and
// function declarations
#include "shell.h"

// Function to read a command from the user input
void read_command(char **cmd)
{
  // Define a character array to store the command line input
  char line[MAX_LINE];
  // Initialize count to keep track of the number of characters read
  int count = 0, i = 0;
  // Array to hold pointers to the parsed command arguments
  char *array[MAX_ARGS], *command_token;

  // Infinite loop to read characters until a newline or maximum line length is
  // reached
      for (;;)
    {
  // Read a single character from standard input
  int current_char = fgetc(stdin);

  // If stdin has closed (user pressed ctrl+D, or piped input ran out), fgetc returns EOF
  if (current_char == EOF)
      {
  // If nothing was typed yet, treat it the same as the user typing exit
  if (count == 0)
        {
  cmd[0] = strdup("exit");
  cmd[1] = NULL;
  return;
        }
  // Otherwise process whatever characters were typed before EOF showed up
  break;
      }

  // Check if the line is about to exceed the maximum length, leaving room for the null terminator
  if (count >= MAX_LINE - 1  && i < MAX_ARGS - 1)
      {
  printf("Command is too long, unable to process\n");
  // Drain the rest of the current line so leftover characters do not get read as the next command
  while (current_char != '\n' && current_char != EOF)
  current_char = fgetc(stdin);
  // Mark this command as empty so the shell just reprints the prompt
  cmd[0] = NULL;
  return;
      }

  // Store the character in the line array and increment count
  line[count++] = (char)current_char;

  // If a newline character is encountered, break out of the loop
  if (current_char == '\n')
  break;
    }
  // Null-terminate the command line string
  line[count] = '\0';

  // If only the newline character was entered, return without processing
  if (count == 1)
    return;

  // Use strtok to parse the first token (word) of the command
  command_token = strtok(line, " \n");

  // Continue parsing the line into words and store them in the array
  while (command_token != NULL)
  {
    array[i++] = strdup(command_token);  // Duplicate the token and store it
    command_token = strtok(NULL, " \n"); // Get the next token
  }

  // Copy the parsed command and its parameters to the cmd array
  for (int j = 0; j < i; j++)
  {
    cmd[j] = array[j];
  }
  // Null-terminate the cmd array to mark the end of arguments
  cmd[i] = NULL;
}

// Function to display the shell prompt
void type_prompt()
{
  // Use a static variable to check if this is the first call to the function
  static int first_time = 1;
  if (first_time)
  {
    // Clear the screen on the first call
#ifdef _WIN32
    system("cls"); // Windows command to clear screen
#else
    system("clear"); // UNIX/Linux command to clear screen
#endif
    first_time = 0;
  }
  fflush(stdout); // Flush the output buffer
  char cwd[1024];
  getcwd(cwd, sizeof(cwd));
  char *username = getlogin();
// getlogin can return NULL if there is no controlling terminal, for example when input is piped or redirected
// printf with a NULL %s argument is undefined behaviour and can crash, so fall back to a placeholder
if (username == NULL)
  {
username = "user";
  }
printf("\033[1;%s%s\033[1;37m:\033[1;%s%s\033[1;37m$$\033[0m ", current_color,username,current_color, cwd);
  // printf("$$ ");  // Print the shell prompt
}



