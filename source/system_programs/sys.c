#include "system_program.h"
#include <sys/sysinfo.h>
#ifdef linux
#include <sys/statvfs.h>
#endif
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
    FILE *f = fopen("/proc/cpuinfo","r");
    if(f==NULL){
        perror("fopen");
        return 1;
    }
    char cpu_model[256];
    char line[256];
    while(fgets(line, sizeof(line),f)){
        if(strncmp(line, "model name",10)==0){
            char *colon = strchr(line,':');
            if(colon){
                snprintf(cpu_model, sizeof(cpu_model),"%s",colon+2);
                cpu_model[strcspn(cpu_model,"\n")]=0;

            }
        }
    }
    struct sysinfo info;
    sysinfo(&info);
    #ifdef linux
    struct statvfs fiData;
    if((statvfs("/",&fiData)) < 0 ) {
                    perror("statvfs");
            }
    #endif
    printf("System name - %s \n", detect.sysname);
    printf("Nodename    - %s \n", detect.nodename);
    printf("Release     - %s \n", detect.release);
    printf("Version     - %s \n", detect.version);
    printf("Machine     - %s \n", detect.machine);
    printf("User name   - %s \n", username);
    printf("Host name   - %s \n", hostname);
    printf("CPU Model   - %s \n", cpu_model);
    printf("Memory      - %.2f GB\n", ((info.totalram/1024.0)/1024.0)/1024.0);
    #ifdef linux
    printf("Disk        - %.2f GB\n",(((fiData.f_blocks*fiData.f_bsize)/1024.0)/1024.0)/1024.0);
    #endif
    return 0;
}