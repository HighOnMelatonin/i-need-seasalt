#include "system_program.h"

int main(int argc, char **args){
    if(args[1]!=NULL){
        printf("Usage: type dcheck to get number of running daemons\n");
        if(strcmp(args[1],"-h")==0){
            return 0;
        }
        return 1;
    }
    FILE *pipe = popen("ps -ef | grep dspawn | grep -Ev 'tty|pts'", "r");
    if (pipe == NULL) {
        perror("popen");
        return 1;
    }
    char buffer[128];
    int daemon_count = 0;
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        daemon_count++;
    }
    pclose(pipe);
    printf("Live daemons: %d\n", daemon_count);
    return 0;
}