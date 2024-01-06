#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/input.h"
#include "../include/tools.h"
#include "../include/commands.h"
#include "../include/execute.h"

void commandDelete(const char *file_path, const char *target){
    // Checks whether one file is being deleted or if we are deleting multiple belonging to some group
    if(target[0] == '*'){
            loopFiles(file_path, &target[1], 'd');
        }else{
            fileDelete(file_path, target);
        }
}

void commandCopy(const char *file_path, const char *target){
    // Checks whether one file is being copied or if we are copying multiple belonging to some group
    if(target[0] == '*'){
        loopFiles(file_path, &target[1], 'c');
    }else{
        fileCopy(file_path, target);
    }
}

void loopFiles(const char *dir_name, const char *search_str, const char option){
    // Calls recursive loop() and initialises layer_depth as can't do this within recursiveLoop()

    uint *layer_depth = (uint*)malloc(sizeof(uint));
    *layer_depth = 0;
    recursiveLoop(dir_name, search_str, option, layer_depth);
    free(layer_depth);
}

void autoRun(const char *file_path){
    // Opens rules.txt and line by line validates and executes each command

    FILE *rule_file;
    char rule[100];
    char rule_filename[] = "./assets/rules.txt";
    size_t line_count = 0;
    LegInp *command = (LegInp*)malloc(sizeof(LegInp));

    // Open a file in read mode
    rule_file = fopen(rule_filename, "r");
    if(rule_file == NULL) {
        printf("Not able to open the file.\n");
    } else{
        printf("Successfully opened rules.txt.\n");
    }

    // Checks validity of rule then executes
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
    char rule_filename[] = "./assets/rules.txt";
    uint line_count = 0;
    // Open a file in read mode
    rule_file = fopen(rule_filename, "r");
    if(rule_file == NULL) {
        printf("Not able to open the file.\n");
    } else{
        printf("Successfully opened rules.txt.\n");
    }
    
    // Fetches each line and prints, adding a numerical index
    while(fgets(line, 100, rule_file)){
        printf("[%d] %s", line_count+1, line);
        line_count++;
    }

    fclose(rule_file);
}

void ruleAdd(){
    // Appends a rule to the end of rules.txt

    FILE *rule_file;
    char rule_input[100];
    char rule_filename[] = "./assets/rules.txt";

    // Open a file in append mode
    rule_file = fopen(rule_filename, "a");
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
    // Edits or deletes a rules according to option

    FILE *file, *temp;

    // store the filename and temp filename
    char filename[] = "./assets/rules.txt";
    char temp_filename[] = "./assets/temp____rules.txt";

    // Will store each line in the file, and the line to select
    char buffer[100];
    int select_line = 0;

    // Have the user enter the line number to alter, store it into select_line
    printf("Enter Line : ");
    scanf("%d", &select_line);
    
    while ((getchar()) != '\n');    // Clears buffer before using fgets
    // Open the original file for reading and the temp file for writing
    file = fopen(filename, "r");
    temp = fopen(temp_filename, "w");
    
    // If there was a problem opening either file let the user know what the error
    // was and exit with a non-zero error status
    if (file == NULL || temp == NULL)
    {
        printf("Error opening file(s)\n");
    }
    
    // Current_line will keep track of the current line number being read
    bool keep_reading = true;
    int current_line = 1;
    do 
    {
        // stores the next line from the file into the buffer
        fgets(buffer, 100, file);

        // Prints each rule, and if current_line and 'e' option is selected, overwrites with user input
        if (feof(file)) keep_reading = false;
        else if (current_line != select_line){
            fputs(buffer, temp);
        }else if(current_line == select_line && option == 'e'){
            char edit_line[100];
            printf("Enter altered rule : ");
            fgets(edit_line, 100, stdin);
            fputs(edit_line, temp);
        }
        
        // Keeps track of the current line being read
        current_line++;
    
    } while (keep_reading);

    // close our access to the files
    fclose(file);
    fclose(temp);
    
    // Delete the original file, give the temp file the name of the original file
    remove(filename);
    rename(temp_filename, filename);
}

void cDirAlter(const char option){
    // Changes the default backup location for files which are copied, or prints

    FILE *dest_path_file;
    char dest_path_filename[] = "./assets/destination_filepath.txt";
    char dest_path[FILEPATH_LENGTH];

    dest_path_file = fopen(dest_path_filename, "r+");
    // Checks which option has been passed
    if(dest_path_file != NULL){
        if(option == 'p'){
            // Fetches the filepath from the file and prints to command line
            fgets(dest_path, FILEPATH_LENGTH, dest_path_file);
            printf("%s", dest_path);
        }else if(option == 'e'){
            // Fetches input filepath from user and replaces that in the file
            printf("Please enter the filepath of the directory you would like files to be copied to : \n");
            fgets(dest_path, FILEPATH_LENGTH, stdin);
            fputs(dest_path, dest_path_file);
        }
    fclose(dest_path_file);
        
    }else{
        printf("Unable to open file containing copy address.");
    }
}