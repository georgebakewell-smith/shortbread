#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "../include/input.h"
#include "../include/tools.h"
#include "../include/commands.h"
#include "../include/execute.h"

void commandCopy(const char *file_path, const char *target, const char *dest_path){

    if(target[0] == '*'){
        listfiles(file_path, &target[1], 'c');
    }else{
        copyfile(file_path, target);
    }

}

void listfiles(const char *dir_name, const char *search_str, const char option){
    //Opens directory
    DIR *dir = opendir(dir_name);
    if(dir == NULL){
        printf("Directory not opened\n");
    }
    
    struct dirent *entity;
    entity = readdir(dir);
    //Cycles through contents
    printf("\n");
    while(entity != NULL){
        if(entity->d_type == DT_REG){
            if(option == 'p'){
                printf("%s", entity->d_name);printf("\n");
            }else if(option == 'c' && checkExtension(entity->d_name, search_str) == 0){
                copyfile(dir_name, entity->d_name);
            }
            
            
        }
        //Calls listfiles() within itself to recursively access folders within
        if(entity->d_type == DT_DIR && strcmp(entity->d_name, ".")!=0 && strcmp(entity->d_name, "..")!=0){
            char path[100] = {0};
            strcat(path, dir_name);
            strcat(path, "/");
            strcat(path, entity->d_name);
            listfiles(path, search_str, option);
        }   
        entity = readdir(dir);
    }
    closedir(dir);
}

void autorun(const char *file_path){

    FILE *rule_file;
    char rule[100];
    size_t line_count = 0;
    LegInp *command = (LegInp*)malloc(sizeof(LegInp));

    // Open a file in read mode
    rule_file = fopen("rules.txt", "r");
    if(rule_file == NULL) {
        printf("Not able to open the file.\n");
    } else{
        printf("Successfully opened rules.txt.\n");
    }

    while(readLine(rule, rule_file) == 0){
    if(isLegit(rule, command) != 1){
            printf("Undefined command. Please try again.\n");           
        }
    excommand(command, file_path);
    
    }
    fclose(rule_file);
    free(command);
}

void printrules(){
    // Prints contents of rules.txt
    FILE *rule_file;
    char ch;
    // Open a file in read mode
    rule_file = fopen("rules.txt", "r");
    if(rule_file == NULL) {
        printf("Not able to open the file.\n");
    } else{
        printf("Successfully opened rules.txt.\n");
    }
    ch = fgetc(rule_file);
    while (ch != EOF){
        
        printf("%c", ch);
        ch = fgetc(rule_file);
    }

    fclose(rule_file);
}

void addrule(){
    FILE *rule_file;
    char rule_input[100];

    // Open a file in append mode
    rule_file = fopen("rules.txt", "a");
    if(rule_file == NULL) {
        printf("Not able to open the file.\n");
    } else{
        printf("Successfully opened rules.txt.\n");
    }
    
    printf("Enter rule : ");
    fgets(rule_input, 100, stdin);
    newLineRemove(rule_input);

    fprintf(rule_file, rule_input);
    fclose(rule_file);
}