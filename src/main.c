#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/input.h"
#include "../include/tools.h"
#include "../include/execute.h"

int main(){

    const unsigned int file_path_length = FILEPATH_LENGTH;
    char *file_path = (char*)malloc(file_path_length*sizeof(char));
    bool exit = false;
    int myint = FILEPATH_LENGTH;
    FILE *rule_file, *destination_path_file;

    // Initialise rules.txt and destination_path.txt
    // Opens in read first to check existence, creates new if file doesn't exist
    rule_file = fopen("./assets/rules.txt", "r");
    destination_path_file = fopen("./assets/destination_filepath.txt", "r");
    if(rule_file == NULL){
        rule_file = fopen("./assets/rules.txt", "w");
        
        if(rule_file != NULL){
            fclose(rule_file);
        }else{
            printf("Error Creating or opening rules.txt, Shortbread will not work.\n");
        }
    }else{
        fclose(rule_file);
    }
    if(destination_path_file == NULL){
        destination_path_file = fopen("./assets/destination_filepath.txt", "w");
        if(destination_path_file != NULL)
        {
            fclose(destination_path_file);
        }else{
            printf("Error Creating or opening destination_filepath.txt, Shortbread will not work.\n");
        }
    }else{
        fclose(destination_path_file);
    }
    // Welcome screen 
    printf("\nWelcome to Shortbread, your new directory cleanup tool!\n\n");
    printf("Please enter your target directory:\n");
    fgets(file_path, file_path_length, stdin);    
    newLineRemove(file_path);
    printToCMD(file_path);

    // Create input pointer, handle and validate, execute then print file_path to command line
    while(exit!=true){
        LegInp *leg_input = (LegInp*)malloc(sizeof(LegInp));
        inputHandle(leg_input, file_path);
        if(strcmp(leg_input->command, "exit") == 0){
            free(leg_input);
            break;
        }
        executeCommand(leg_input, file_path);
        printToCMD(file_path);
        free(leg_input);
        
    }
    
    free(file_path);
    
return 0;
}