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
    long pages = sysconf(_SC_PHYS_PAGES);
    long page_size = sysconf(_SC_PHYS_PAGES);
    long long total_bytes = (long long)pages *page_size;
    double total_gb = (double)total_bytes/(1024*1024*1024);
    printf("System name - %s \n", detect.sysname);
    printf("Nodename    - %s \n", detect.nodename);
    printf("Release     - %s \n", detect.release);
    printf("Version     - %s \n", detect.version);
    printf("Machine     - %s \n", detect.machine);
    #ifdef __linux__
    printf("Domain name - %s \n", detect.__domainname);
    #else
    printf("Domain name - not available on this system\n");
    #endif
    printf("User name   - %s \n", username);
    printf("Host name   - %s \n", hostname);
    printf("CPU Model   - %s \n", cpu_model);
    printf("Memory      - %.2f GB\n", total_gb);
    return 0;
}