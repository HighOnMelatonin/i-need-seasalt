#include "system_program.h"

int main(int argc, char **args){
    if(args[1]!=NULL){
        printf("Usage: type backup to backup BACKUP_DIR\n");
        if(strcmp(args[1],"-h")==0){
            return 0;
        }
        return 1;
    }
    char *backup_dir = getenv("BACKUP_DIR");
    if(backup_dir==NULL){
        printf("Error: Set backup directory\n type setenv BACKUP_DIR path/to/dir\n");
        return 1;
    }
    time_t current_time = time(NULL);
    struct tm *time_info = localtime(&current_time);
    char archivepath[256];
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y%m%d%H%M%S", time_info);
    snprintf(archivepath, sizeof(archivepath), "%s/../backup-%s.zip",backup_dir,timestamp);
    printf("Creating backup of %s at %s\n", backup_dir, timestamp);
    char system_call[256];
    snprintf(system_call, sizeof(system_call),"zip -r %s %s",archivepath,backup_dir);
    system(system_call);

}