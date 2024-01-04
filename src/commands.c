#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/input.h"
#include "../include/tools.h"
#include "../include/commands.h"
#include "../include/execute.h"

void commandDelete(const char *file_path, const char *target){
    if(target[0] == '*'){
            loopFiles(file_path, &target[1], 'd');
        }else{
            fileDelete(file_path, target);
        }
}

void commandCopy(const char *file_path, const char *target, const char *dest_path){
    if(target[0] == '*'){
        loopFiles(file_path, &target[1], 'c');
    }else{
        fileCopy(file_path, target);
    }
}

void loopFiles(const char *dir_name, const char *search_str, const char option){
    uint *layer_depth = (uint*)malloc(sizeof(uint));
    *layer_depth = 0;
    recursiveLoop(dir_name, search_str, option, layer_depth);
    free(layer_depth);
}

void autoRun(const char *file_path){

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
    executeCommand(command, file_path);
    
    }
    fclose(rule_file);
    free(command);
}

void rulePrint(){
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

void ruleAdd(){
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

    fprintf(rule_file, rule_input);
    fclose(rule_file);
}

void ruleAlter(const char option){

    FILE *file, *temp;

    // store the filename and temp filename
    char filename[] = "rules.txt";
    char temp_filename[100];

    // will store each line in the file, and the line to select
    char buffer[100];
    int select_line = 0;
    
    strcpy(temp_filename, "temp____");
    strcat(temp_filename, filename);

    // have the user enter the line number to alter, store it into select_line
    printf("Enter Line : ");
    scanf("%d", &select_line);
    
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
  
        if (feof(file)) keep_reading = false;
        else if (current_line != select_line){
            fputs(buffer, temp);
        }else if(current_line == select_line && option == 'e'){
            char edit_line[100];
            printf("Enter altered rule : ");
            while ((getchar()) != '\n');
            fgets(edit_line, 100, stdin);
            fputs(edit_line, temp);
        }
        
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