#include "resource_usage.h"
#include <stdio.h>

static double timeval_diff_seconds(struct timeval start, struct timeval end)
{
    return (end.tv_sec - start.tv_sec) +
           (end.tv_usec - start.tv_usec) / 1000000.0;
}

void get_resource_snapshot(struct rusage *usage, bool is_builtin)
{
    if (is_builtin)
        getrusage(RUSAGE_SELF, usage);
    else
        getrusage(RUSAGE_CHILDREN, usage);
}

void print_resource_usage(const char *command_name,
                           struct rusage before,
                           struct rusage after)
{
    double user_cpu = timeval_diff_seconds(before.ru_utime, after.ru_utime);
    double system_cpu = timeval_diff_seconds(before.ru_stime, after.ru_stime);
    double total_cpu = user_cpu + system_cpu;
    long memory_kb = after.ru_maxrss;
    long disk_reads = after.ru_inblock - before.ru_inblock;
    long disk_writes = after.ru_oublock - before.ru_oublock;

    printf("\nResource usage for '%s':\n", command_name);
    printf("CPU time    : %.6f seconds\n", total_cpu);
    printf("User CPU    : %.6f seconds\n", user_cpu);
    printf("System CPU  : %.6f seconds\n", system_cpu);
    printf("Memory      : %ld KB\n", memory_kb);
    printf("Disk reads  : %ld blocks\n", disk_reads);
    printf("Disk writes : %ld blocks\n\n", disk_writes);
}