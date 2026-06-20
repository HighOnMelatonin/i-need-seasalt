#include "unity.h"
#include "shell.h"
#include <stdlib.h>

void setUp(void) {}

void tearDown(void)
{
    unsetenv("TEST_PA1_UNIT");
}

/* setenv with KEY=VALUE should create the variable */
void test_setenv_var_sets_environment_variable(void)
{
    char *args[] = {"setenv", "TEST_PA1_UNIT=hello", NULL};

    int result = setenv_var(args);

    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_EQUAL_STRING("hello", getenv("TEST_PA1_UNIT"));
}

/* setenv without KEY=VALUE should fail */
void test_setenv_missing_value_returns_1(void)
{
    char *args[] = {"setenv", "TEST_PA1_UNIT", NULL};

    TEST_ASSERT_EQUAL_INT(1, setenv_var(args));
}

/* unsetenv should remove an existing variable */
void test_unsetenv_var_removes_environment_variable(void)
{
    setenv("TEST_PA1_UNIT", "hello", 1);

    char *args[] = {"unsetenv", "TEST_PA1_UNIT", NULL};

    int result = unsetenv_var(args);

    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_NULL(getenv("TEST_PA1_UNIT"));
}

/* unsetenv without variable name should fail */
void test_unsetenv_missing_argument_returns_1(void)
{
    char *args[] = {"unsetenv", NULL};

    TEST_ASSERT_EQUAL_INT(1, unsetenv_var(args));
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_setenv_var_sets_environment_variable);
    RUN_TEST(test_setenv_missing_value_returns_1);
    RUN_TEST(test_unsetenv_var_removes_environment_variable);
    RUN_TEST(test_unsetenv_missing_argument_returns_1);

    return UNITY_END();
}