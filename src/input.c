#include <stdio.h>
#include <stdlib.h>

int isLegit(char *userInput);


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

}

int isLegit(char *userInput){
    printf("Successfully entered function\n");
    return 0;
}