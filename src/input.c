#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isLegit(char *userInput);
void scanInput(char *userInput);


void handleInput(){

    size_t inpLen = 60;
    char *userInput = (char*)malloc(inpLen*sizeof(char));

    fgets(userInput, inpLen, stdin);
    printf("The command you entered is : %s", userInput);
    if(isLegit(userInput)){
        printf("Legit!\n");
    }else{
        printf("Undefined command. Please try again.\n");
    }

    free(userInput);
}

void scanInput(char *userInput){

    char delim[] = " ";
    char* token = strtok(userInput, delim);

    while (token != NULL) {
        printf(" %s\n", token);
        token = strtok(NULL, delim);
    }
}

int isLegit(char *userInput){
    scanInput(userInput);

    return 1;
}