#include "system_program.h"

int main(int argc, char **args){
    if(args[1]!=NULL){
        printf("Usage: type sys to get system information\n");
        if(strcmp(args[1],"-h")==0){
            return 0;
        }
        return 1;
    }

    struct utsname detect;
    if(uname(&detect)!=0){
        perror("uname");
        return 1;
    }

    char *username = getlogin();

    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) != 0) {
        snprintf(hostname, sizeof(hostname), "unknown");
    }

    printf("System name - %s \n", detect.sysname);
    printf("Nodename    - %s \n", detect.nodename);
    printf("Release     - %s \n", detect.release);
    printf("Version     - %s \n", detect.version);
    printf("Machine     - %s \n", detect.machine);
    //printf("Domain name - %s \n", detect.__domainname);
    printf("User name   - %s \n", username);
    printf("Host name   - %s \n", hostname);
    return 0;
}