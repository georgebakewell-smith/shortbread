#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void newLineRemove(char *myStr){
    size_t inpLen;
    inpLen = strlen(myStr);
        *(myStr+inpLen-1) = '\0';
}