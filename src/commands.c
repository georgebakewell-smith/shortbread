#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "../include/input.h"
#include "../include/tools.h"
#include "../include/commands.h"

void listfiles(const char *dirname){
    //Opens directory
    DIR *dir = opendir(dirname);
    if(dir == NULL){
        printf("Directory not opened\n");
    }
    
struct dirent *entity;
entity = readdir(dir);
//Cycles through contents
printf("\n");
while(entity != NULL){
    if(entity->d_type == DT_REG){
        printf("%s", entity->d_name);printf("\n");
        
    }
    //Calls listfiles() within itself to recursively access folders within
    if(entity->d_type == DT_DIR && strcmp(entity->d_name, ".")!=0 && strcmp(entity->d_name, "..")!=0){
        char path[100] = {0};
        strcat(path, dirname);
        strcat(path, "/");
        strcat(path, entity->d_name);
        listfiles(path);
    }
    
    entity = readdir(dir);
}
    closedir(dir);
}