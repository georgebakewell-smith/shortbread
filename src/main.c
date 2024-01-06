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

    printf("\nWelcome to Shortbread, your new directory cleanup tool!\n\n");
    printf("Please enter your target directory:\n");
    // fgets(file_path, file_path_length, stdin); //remove for now to save time when testing, use hardcoded line below for testing
    strcpy(file_path, "/home/george/Documents/cprojects/shortbreadtestfiles/");
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