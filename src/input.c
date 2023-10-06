#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/tools.h"
//#include "../include/leg_inp.h"
#include "../include/input.h"

int isLegit(char *userInput, leginp *pLegInp);

void handleInput(leginp *pLegInp, char *filePath){

    size_t inpLen = 60;
    size_t commandLen = 20;
    char *userInput = (char*)malloc(inpLen*sizeof(char));
    char *command = (char*)malloc(commandLen*sizeof(char));
    
    do{
        //Takes user input
        fgets(userInput, inpLen, stdin);  
        newLineRemove(userInput);

        //Checks command is legitimate
        if(isLegit(userInput, pLegInp)){
            
            break;

        }else{
            printf("Undefined command. Please try again.\n");
            cmdprint(filePath);
        }
    }while(1);

    
    
    
    
    free(command);
    free(userInput);
}



int isLegit(char *userInput, leginp *pLegInp){  
    size_t tokenCount = 0;

    //Breaks input into tokens
    char delim[] = " ";
    char* token = strtok(userInput, delim);
    
    while (token != NULL) {
        ++tokenCount;
        if(tokenCount==1){           
            strcpy(pLegInp->command, token);           
        }

        //printf("%s",token);
        if(tokenCount==2){
            strcpy(pLegInp->target, token);
            
            
        }

       
        token = strtok(NULL, delim);
        
        
    }
    pLegInp->numTokens = tokenCount;

    //Checks if less than 2 tokens
    if(tokenCount <= 2){     
        return 1;
    }else{
        return 0;
    };

}