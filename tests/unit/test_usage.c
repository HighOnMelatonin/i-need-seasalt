//gives access to unity testing framework
#include "unity.h"
#include "usage.h"

// * Tested scenarios:
 /* 1. Missing command argument
 * 2. Valid builtin command
 * 3. Invalid command 
void setUp(void) {}*/

//calls the function shell(args) without running the whole shell - test small functions only 

//unity auto calls setup before every test and teardown after every test
void setUp(void) {}
void tearDown(void) {}

void test_usage_no_argument_returns_1(void)
{
    //NULL because fcuntions need to know where the list ends
    // Test Case:
// Simulates user typing: usage
// Expected:
// Function should detect missing command argument
// Function should return status code 1
    char *args[] = {"usage", NULL};
    TEST_ASSERT_EQUAL_INT(1, shell_usage(args));
}

void test_usage_cd_returns_1(void)
{
    // Test Case:
// Simulates user typing: usage cd
// Expected:
// Function should display usage information for cd
// Function should return status code 1
    char *args[] = {"usage", "cd", NULL};
    TEST_ASSERT_EQUAL_INT(1, shell_usage(args));
}

void test_usage_invalid_command_returns_1(void)
{
    // Test Case:
// Simulates user typing: usage banana
// Expected:
// Function should identify command as invalid
// Function should not crash
// Function should return status code 1
    char *args[] = {"usage", "banana", NULL};
    TEST_ASSERT_EQUAL_INT(1, shell_usage(args));
}


//test programs main
int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_usage_no_argument_returns_1);
    RUN_TEST(test_usage_cd_returns_1);
    RUN_TEST(test_usage_invalid_command_returns_1);

    return UNITY_END();
}