#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/tools.h"

void newLineRemove(char *myStr){
    size_t inpLen;
    inpLen = strlen(myStr);
        *(myStr+inpLen-1) = '\0';
}

void cmdprint(char *myStr){
    printf("\n%s", myStr);
}