#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "../include/input.h"
#include "../include/tools.h"
#include "../include/commands.h"
#include "../include/execute.h"

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

void autorun(const char *filePath){

    FILE *ruleFile;
    char rule[100];
    size_t nlineCount = 0;
    leginp *pRuleCom = (leginp*)malloc(sizeof(leginp));

    // Open a file in read mode
    ruleFile = fopen("rules.txt", "r");
    if(ruleFile == NULL) {
        printf("Not able to open the file.\n");
    }

    while(readLine(rule, ruleFile) == 0){
    if(isLegit(rule, pRuleCom) != 1){
            printf("Undefined command. Please try again.\n");           
        }
    excommand(pRuleCom, filePath);
    }
    fclose(ruleFile);
    free(pRuleCom);
}