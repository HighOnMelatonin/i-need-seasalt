#include "system_program.h"

char output_file_path[PATH_MAX];
static int daemon_work()
{
    int num=0;
    FILE *fptr;
    char *cwd;
    char buffer[1024];
    // write PID of daemon in the beginning
    fptr=fopen(output_file_path,"a");
    if(fptr==NULL)
    {
        return EXIT_FAILURE;
    }
    fprintf(fptr,"Daemon process running with PID: %d, PPID: %d, opening logfile with FD %d\n",getpid(),getppid(),fileno(fptr));
    // then write cwd
    cwd=getcwd(buffer,sizeof(buffer));
    if(cwd==NULL)
    {
        perror("getcwd() error");
        return 1;
    }
    fprintf(fptr,"Current working directory: %s\n",cwd);
    fclose(fptr);
    while(1)
    {
        // use appropriate location if you are using MacOS or Linux
        fptr=fopen(output_file_path,"a");
        if(fptr==NULL)
        {
            return EXIT_FAILURE;
        }
        fprintf(fptr,"PID %d Daemon writing line %d to the file.  \n",getpid(),num);
        num++;
        fclose(fptr);
        sleep(10);
        if(num==10){
            // we just let this process terminate after 10 counts
            break;}
    }
    return EXIT_SUCCESS;
}


int main(int argc, char **args){

    if(args[1]!=NULL){
        printf("Usage: type dspawn to spawn a daemon!\n");
        if(strcmp(args[1],"-h")==0){
            return 0;
        }
        return 1;
    }

    if(getcwd(output_file_path,sizeof(output_file_path))==NULL)
    {
    perror("getcwd() error, exiting now.");
    return 1;
    }
    strcat(output_file_path,"/dspawn.log");

    pid_t pid = fork();

    if(pid > 0){
        exit(0);
    }

    setsid();

    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    pid_t pid2 = fork();

    if(pid2>0){
        exit(0);
    }

    umask(0);

    chdir("/");

    int x;
    for(x=sysconf(_SC_OPEN_MAX);x>=0;x--)
    {
    close(x);
    }
    /*
    * Attach file descriptors 0, 1, and 2 to /dev/null. */
    int fd0=open("/dev/null",O_RDWR);
    int fd1=open("/dev/null",O_RDWR);
    int fd2=open("/dev/null",O_RDWR);
    daemon_work();
}
