#include "unity.h"
#include "shell.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Helper function to get the history file path
static char* get_history_path(void) {
    static char historypath[PATH_MAX];
    char *username = getlogin();
    if (username == NULL) {
        username = "user";
    }
    snprintf(historypath, sizeof(historypath), "/home/%s/.ss_history", username);
    return historypath;
}

// Helper function to read history file contents into a string
static char* read_history_file(void) {
    FILE *file = fopen(get_history_path(), "r");
    if (file == NULL) {
        return NULL;
    }
    
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    if (size == 0) {
        fclose(file);
        char *empty = malloc(1);
        empty[0] = '\0';
        return empty;
    }
    
    char *buffer = malloc(size + 1);
    fread(buffer, 1, size, file);
    buffer[size] = '\0';
    fclose(file);
    
    return buffer;
}

// Helper function to count lines in history file
static int count_history_lines(void) {
    char *content = read_history_file();
    if (content == NULL) {
        return 0;
    }
    
    int count = 0;
    for (int i = 0; content[i] != '\0'; i++) {
        if (content[i] == '\n') {
            count++;
        }
    }
    free(content);
    return count;
}

void setUp(void) {
    // Clean state before each test
    clear_history();
}

void tearDown(void) {
    // Clean up after each test
    clear_history();
    char *file = get_history_path();
    if (file != NULL) {
        remove(file);
    }
}

void test_clear_history_succeeds(void) {
    // Add a command first
    char *cmd[] = {"test_command", NULL};
    add_history(cmd);
    
    // Verify command was added
    char *content = read_history_file();
    TEST_ASSERT_NOT_NULL(content);
    TEST_ASSERT_TRUE(strlen(content) > 0);
    free(content);
    
    // Clear history
    int result = clear_history();
    TEST_ASSERT_EQUAL_INT(0, result);
    
    // Verify history is now empty
    content = read_history_file();
    TEST_ASSERT_NOT_NULL(content);
    TEST_ASSERT_EQUAL_INT(0, strlen(content));
    free(content);
}

void test_clear_history_with_empty_file(void) {
    // Clear history on empty file should still succeed
    int result = clear_history();
    TEST_ASSERT_EQUAL_INT(0, result);
}

void test_add_history_single_command(void) {
    char *cmd[] = {"ls", NULL};
    int result = add_history(cmd);
    
    TEST_ASSERT_EQUAL_INT(0, result);
    
    // Verify it was written to file
    char *content = read_history_file();
    TEST_ASSERT_NOT_NULL(content);
    TEST_ASSERT_TRUE(strstr(content, "ls") != NULL);
    free(content);
}

void test_add_history_multiple_commands(void) {
    char *cmd1[] = {"ls", NULL};
    char *cmd2[] = {"cd", NULL};
    char *cmd3[] = {"pwd", NULL};
    
    add_history(cmd1);
    add_history(cmd2);
    add_history(cmd3);
    
    // Should have 3 lines
    int lines = count_history_lines();
    TEST_ASSERT_EQUAL_INT(3, lines);
    
    // All commands should be present
    char *content = read_history_file();
    TEST_ASSERT_TRUE(strstr(content, "ls") != NULL);
    TEST_ASSERT_TRUE(strstr(content, "cd") != NULL);
    TEST_ASSERT_TRUE(strstr(content, "pwd") != NULL);
    free(content);
}

void test_add_history_with_null_command(void) {
    char *cmd[] = {NULL};
    int result = add_history(cmd);
    
    // Should return failure
    TEST_ASSERT_EQUAL_INT(EXIT_FAILURE, result);
}

void test_add_history_appends_to_file(void) {
    char *cmd1[] = {"first", NULL};
    char *cmd2[] = {"second", NULL};
    
    add_history(cmd1);
    add_history(cmd2);
    
    char *content = read_history_file();
    TEST_ASSERT_NOT_NULL(content);
    
    // Both should be present and "first" should come before "second"
    char *first_pos = strstr(content, "first");
    char *second_pos = strstr(content, "second");
    TEST_ASSERT_NOT_NULL(first_pos);
    TEST_ASSERT_NOT_NULL(second_pos);
    TEST_ASSERT_TRUE(first_pos < second_pos);
    
    free(content);
}

void test_add_history_with_arguments(void) {
    char *cmd[] = {"echo", "hello", "world", NULL};
    int result = add_history(cmd);
    
    TEST_ASSERT_EQUAL_INT(1, result);
    
    // Only first argument should be stored
    char *content = read_history_file();
    TEST_ASSERT_FALSE(strstr(content, "echo") != NULL);
    free(content);
}

void test_get_history_no_arguments(void) {
    // Add some commands first
    char *cmd1[] = {"ls", NULL};
    char *cmd2[] = {"cd", NULL};
    add_history(cmd1);
    add_history(cmd2);
    
    // Call get_history with no arguments (should print to stdout)
    char *args[] = {NULL};
    int result = get_history(args);
    
    TEST_ASSERT_EQUAL_INT(1, result);
}

void test_get_history_with_help_flag(void) {
    char *args[] = {"history", "-h", NULL};
    int result = get_history(args);
    
    // Should return 0 for help
    TEST_ASSERT_EQUAL_INT(0, result);
}

void test_get_history_with_invalid_flag(void) {
    char *args[] = {"history", "--invalid", NULL};
    int result = get_history(args);
    
    // Should return 1 for invalid arguments
    TEST_ASSERT_EQUAL_INT(1, result);
}

void test_history_file_format_newlines(void) {
    char *cmd1[] = {"command1", NULL};
    char *cmd2[] = {"command2", NULL};
    char *cmd3[] = {"command3", NULL};
    
    add_history(cmd1);
    add_history(cmd2);
    add_history(cmd3);
    
    // Each command should be on its own line
    int lines = count_history_lines();
    TEST_ASSERT_EQUAL_INT(3, lines);
}

int main(void) {
    UNITY_BEGIN();

    printf("TESTING CMDSCROLL\n\n");
    
    RUN_TEST(test_clear_history_succeeds);
    RUN_TEST(test_clear_history_with_empty_file);
    RUN_TEST(test_add_history_single_command);
    RUN_TEST(test_add_history_multiple_commands);
    RUN_TEST(test_add_history_with_null_command);
    RUN_TEST(test_add_history_appends_to_file);
    RUN_TEST(test_add_history_with_arguments);
    RUN_TEST(test_get_history_no_arguments);
    RUN_TEST(test_get_history_with_help_flag);
    RUN_TEST(test_get_history_with_invalid_flag);
    RUN_TEST(test_history_file_format_newlines);
    
    return UNITY_END();
}