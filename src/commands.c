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
    LegInp *pRuleCom = (LegInp*)malloc(sizeof(LegInp));

    // Open a file in read mode
    ruleFile = fopen("rules.txt", "r");
    if(ruleFile == NULL) {
        printf("Not able to open the file.\n");
    } else{
        printf("Successfully opened rules.txt.\n");
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

void printrules(){
    // Prints contents of rules.txt
    FILE *ruleFile;
    char ch;
    // Open a file in read mode
    ruleFile = fopen("rules.txt", "r");
    if(ruleFile == NULL) {
        printf("Not able to open the file.\n");
    } else{
        printf("Successfully opened rules.txt.\n");
    }
    ch = fgetc(ruleFile);
    while (ch != EOF){
        
        printf("%c", ch);
        ch = fgetc(ruleFile);
    }

    fclose(ruleFile);
}

void addrule(){
    FILE *ruleFile;
    char ruleInput[100];

    // Open a file in append mode
    ruleFile = fopen("rules.txt", "a");
    if(ruleFile == NULL) {
        printf("Not able to open the file.\n");
    } else{
        printf("Successfully opened rules.txt.\n");
    }
    
    printf("Enter rule : ");
    fgets(ruleInput, 100, stdin);
    newLineRemove(ruleInput);

    fprintf(ruleFile, ruleInput);
    fclose(ruleFile);
}