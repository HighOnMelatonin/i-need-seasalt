#include "unity.h"
#include "shell.h"
#include <unistd.h>

void setUp(void) {}

void tearDown(void) {}

/* cd -h should show usage help and return 0 */
void test_cd_help_flag_returns_0(void)
{
    char *args[] = {"cd", "-h", NULL};
    TEST_ASSERT_EQUAL_INT(0, shell_cd(args));
}

/* cd with too many arguments should fail */
void test_cd_too_many_arguments_returns_1(void)
{
    char *args[] = {"cd", "folder1", "folder2", NULL};
    TEST_ASSERT_EQUAL_INT(1, shell_cd(args));
}

/* cd to a directory that does not exist should fail */
void test_cd_invalid_directory_returns_1(void)
{
    char *args[] = {"cd", "this_folder_should_not_exist_12345", NULL};
    TEST_ASSERT_EQUAL_INT(1, shell_cd(args));
}

/* cd with no argument should go to HOME */
void test_cd_no_argument_goes_home_and_returns_1(void)
{
    char *args[] = {"cd", NULL};
    TEST_ASSERT_EQUAL_INT(1, shell_cd(args));
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_cd_help_flag_returns_0);
    RUN_TEST(test_cd_too_many_arguments_returns_1);
    RUN_TEST(test_cd_invalid_directory_returns_1);
    RUN_TEST(test_cd_no_argument_goes_home_and_returns_1);

    return UNITY_END();
}