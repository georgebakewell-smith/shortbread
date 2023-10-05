#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/tools.h"
#include "../include/leg_inputs.h"

int isLegit(char *userInput);
size_t scanInput(char *userInput);

void handleInput(){

    size_t inpLen = 60;
    size_t commandLen = 20;
    char *userInput = (char*)malloc(inpLen*sizeof(char));
    char *command = (char*)malloc(commandLen*sizeof(char));
    leginp *pLegInp = (struct LegInputs*)malloc(sizeof(leginp));
    

    //Takes user input
    fgets(userInput, inpLen, stdin);  
    newLineRemove(userInput);

    //Checks command is legitimate
    if(isLegit(userInput)){
        printf("Legit!\n");
    }else{
        printf("Undefined command. Please try again.\n");
    }
    
    
    free(pLegInp);
    free(command);
    free(userInput);
}


size_t scanInput(char *userInput){
    size_t tokenCount = 0;

    char delim[] = " ";
    char* token = strtok(userInput, delim);

    while (token != NULL) {
        ++tokenCount;
        printf("%s\n", token);
        token = strtok(NULL, delim);
    }
    return tokenCount;
}

int isLegit(char *userInput){  

    if(scanInput(userInput) <= 2){
        return 1;
    }else{
        return 0;
    };

}