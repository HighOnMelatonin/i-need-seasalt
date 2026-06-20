#include "shell.h"

char *current_color ="32m";

int color_check(char color[]){
    char *colors_name[] = {
    "red",    
    "green",  
    "yellow", 
    "blue", 
    "magenta",
    "cyan",
    "white"
    };
        for (int color_index = 0; color_index < 7 ; color_index++)
        {
        
        if (strcmp(color, colors_name[color_index]) == 0)
        {

        return (color_index);
        }
        
    }return -2;}

int shell_setcolor(char **args){
    char *colors_list[]= {
    "31m",   
    "32m",
    "33m",
    "34m",
    "35m",
    "36m",
    "37m"
    };

if(args[2]!=NULL || args[1]==NULL){
    printf("Usage: setcolor [colr], to change prompt color to colr\nOR setcolor -supported, to get supported colors\n");
    return 1;
}
if(strcmp(args[1],"-h")==0){
    printf("Usage: setcolor [colr], to change prompt color to colr\nOR setcolor -supported, to get supported colors\n");
    return 0;
}
if(strcmp(args[1],"-supported")==0){
    printf("\033[1msupproted colors are:-\033[0m\n");
    printf("red\ngreen\nyellow\nblue\nmagenta\ncyan\nwhite\n");    
}
int color_index = color_check(args[1]);
if(color_index!=-2){
    current_color = colors_list[color_index];
    return 0;
}
printf("color not found\nType setcolor -supported, to get supported colors\n");
return 1;
}

