#include <stdio.h>
#include <stdlib.h>
#include "../include/input.h"

int main(){

    const unsigned int filePathLength = 60;
    char *filePath = (char*)malloc(filePathLength*sizeof(char));

    printf("\nWelcome to Shortbread, your new directory cleanup tool!\n\n");
    printf("Please enter your target directory:\n");
    fgets(filePath, filePathLength, stdin);
    printf("%s", filePath);
    helloWorld();


    free(filePath);

return 0;
}