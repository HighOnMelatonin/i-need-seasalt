/*
 * test_clear.c
 *
 * Unit tests for shell_clear().
 *
 * Tested scenarios:
 * 1. clear with no extra arguments.
 *
 * Objective:
 * Verify that shell_clear can be called safely and returns success.
 */

#include "unity.h"
#include "shell.h"

void setUp(void) {}
void tearDown(void) {}

void test_clear_returns_0(void)
{
    char *args[] = {"clear", NULL};

    TEST_ASSERT_EQUAL_INT(0, shell_clear(args));
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_clear_returns_0);

    return UNITY_END();
}