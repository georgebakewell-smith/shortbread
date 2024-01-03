#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include "../include/input.h"
#include "../include/tools.h"
#include "../include/commands.h"
#include "../include/execute.h"

void commandDelete(const char *file_path, const char *target){
    if(target[0] == '*'){
            listfiles(file_path, &target[1], 'd');
        }else{
            delfile(file_path, target);
        }
}

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
            else if(option == 'd' && checkExtension(entity->d_name, search_str) == 0){
                delfile(dir_name, entity->d_name);
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
    char ch, line[100];
    uint line_count = 0;
    // Open a file in read mode
    rule_file = fopen("rules.txt", "r");
    if(rule_file == NULL) {
        printf("Not able to open the file.\n");
    } else{
        printf("Successfully opened rules.txt.\n");
    }
 
    while(fgets(line, 100, rule_file)){
        printf("[%d] %s", line_count+1, line);
        line_count++;
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
    //newLineRemove(rule_input);

    fprintf(rule_file, rule_input);
    fclose(rule_file);
}

void ruleDelete(){

    FILE *file, *temp;

    // store the filename and temp filename
    char filename[] = "rules.txt";
    char temp_filename[100];

    // will store each line in the file, and the line to delete
    char buffer[100];
    int delete_line = 0;
    
    strcpy(temp_filename, "temp____");
    strcat(temp_filename, filename);
    
    // have the user enter the line number to delete, store it into delete_line
    printf("Delete Line : ");
    scanf("%d", &delete_line);
    
    // open the original file for reading and the temp file for writing
    file = fopen(filename, "r");
    temp = fopen(temp_filename, "w");
    
    // if there was a problem opening either file let the user know what the error
    // was and exit with a non-zero error status
    if (file == NULL || temp == NULL)
    {
        printf("Error opening file(s)\n");
    }
    
    // current_line will keep track of the current line number being read
    bool keep_reading = true;
    int current_line = 1;
    do 
    {
        // stores the next line from the file into the buffer
        fgets(buffer, 100, file);
    
        // if we've reached the end of the file, stop reading from the file, 
        // otherwise so long as the current line is NOT the line we want to 
        // delete, write it to the file
        if (feof(file)) keep_reading = false;
        else if (current_line != delete_line)
        fputs(buffer, temp);
        
        // keeps track of the current line being read
        current_line++;
    
    } while (keep_reading);
    
    // close our access to the files
    fclose(file);
    fclose(temp);
    
    // delete the original file, give the temp file the name of the original file
    remove(filename);
    rename(temp_filename, filename);

}