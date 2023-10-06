#include <stdio.h>
#include <stdlib.h>
#include "../include/input.h"
#include "../include/tools.h"
//#include "../include/leg_inp.h"

int main(){

    const unsigned int filePathLength = 60;
    char *filePath = (char*)malloc(filePathLength*sizeof(char));
    
    leginp *pLegInp = (leginp*)malloc(sizeof(leginp));
    
    printf("\nWelcome to Shortbread, your new directory cleanup tool!\n\n");
    printf("Please enter your target directory:\n");
    fgets(filePath, filePathLength, stdin);
    newLineRemove(filePath);
    cmdprint(filePath);

    
    
    handleInput(pLegInp, filePath);
        

    free(pLegInp);
    free(filePath);
    printf("Freed successfully!");
return 0;
}