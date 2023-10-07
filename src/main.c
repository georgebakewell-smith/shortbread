#include <stdio.h>
#include <stdlib.h>
#include "../include/input.h"
#include "../include/tools.h"
#include "../include/execute.h"

int main(){

    const unsigned int filePathLength = 60;
    char *filePath = (char*)malloc(filePathLength*sizeof(char));  
    leginp *pLegInp = (leginp*)malloc(sizeof(leginp));
    
    printf("\nWelcome to Shortbread, your new directory cleanup tool!\n\n");
    printf("Please enter your target directory:\n");
    //fgets(filePath, filePathLength, stdin); remove for now to save time when testing, use hardcoded line below for testing
    strcpy(filePath, "/home/george/Documents/cprojects/shortbreadtestfiles/");
    newLineRemove(filePath);
    cmdprint(filePath);
        
    handleInput(pLegInp, filePath);
    excommand(pLegInp, filePath);

    free(pLegInp);
    free(filePath);
    
return 0;
}