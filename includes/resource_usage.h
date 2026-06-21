#ifndef RESOURCE_USAGE_H
#define RESOURCE_USAGE_H

#include <sys/resource.h>
#include <stdbool.h>                                          

void get_resource_snapshot(struct rusage *usage, bool is_builtin); 


void print_resource_usage(const char *command_name,
                          struct rusage before,
                          struct rusage after);

#endif