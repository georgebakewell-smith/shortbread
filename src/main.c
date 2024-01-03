#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/input.h"
#include "../include/tools.h"
#include "../include/execute.h"

int main(){

    const unsigned int file_path_length = 100;
    char *file_path = (char*)malloc(file_path_length*sizeof(char));
    bool exit = false;
    
    printf("\nWelcome to Shortbread, your new directory cleanup tool!\n\n");
    printf("Please enter your target directory:\n");
    //fgets(file_path, file_pathLength, stdin); remove for now to save time when testing, use hardcoded line below for testing
    strcpy(file_path, "/home/george/Documents/cprojects/shortbreadtestfiles/");
    newLineRemove(file_path);
    cmdprint(file_path);
    while(exit!=true){
        LegInp *leg_input = (LegInp*)malloc(sizeof(LegInp));
        handleInput(leg_input, file_path);
        if(strcmp(leg_input->command, "exit") == 0){
            free(leg_input);
            break;
        }
        excommand(leg_input, file_path);
        cmdprint(file_path);
        free(leg_input);
        
    }
    

    
    free(file_path);
    
return 0;
}