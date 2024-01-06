#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/tools.h"
#include "../include/input.h"

void inputHandle(LegInp *leg_input, char *file_path){

    size_t input_length = 60;
    size_t command_length = 20;
    char *user_input = (char*)malloc(input_length*sizeof(char));
    char *command = (char*)malloc(command_length*sizeof(char));
    
    do{
        //Takes user input
        fgets(user_input, input_length, stdin);  
        newLineRemove(user_input);

        //Checks command is legitimate
        if(isLegit(user_input, leg_input)){
            
            break;

        }else{
            printf("\nUndefined command. Please try again.\n");
            printToCMD(file_path);
        }
    }while(1);
    
    free(command);
    free(user_input);
}

int isLegit(char *user_input, LegInp *leg_input){  
    size_t token_count = 0;

    //Breaks input into tokens
    char delim[] = " ";
    char* token = strtok(user_input, delim);
    
    while (token != NULL) {
        ++token_count;
        if(token_count==1){           
            strcpy(leg_input->command, token);           
        }

        //printf("%s",token);
        if(token_count==2){
            strcpy(leg_input->target, token); 
        }

        token = strtok(NULL, delim);
        
    }
    leg_input->num_tokens = token_count;

    //Checks if less than 2 tokens
    if(token_count <= 2){     
        return 1;
    }else{
        return 0;
    };

}