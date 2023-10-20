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
    printf("\n%s$", myStr);
}

void copyfile(const char *filePath, const char *file){
    unsigned char buffer[1024];
    size_t bytesRead;
    FILE *sourceFile, *destFile;
    //Create full filepath with filePath and target file
    //Should probably create function for this and add to tools
    char pathSource[100], pathDest[100];
    strcpy(pathSource, filePath);
    strcat(pathSource, "/");
    strcat(pathSource, file);
    strcpy(pathDest, "/home/george/Documents/cprojects/copiedfiles");
    strcat(pathDest, "/");
    strcat(pathDest, file);
    
    sourceFile = fopen(pathSource, "rb");
    
        if(sourceFile == NULL){
                printf("Error opening source file\n");
                
        }else{
            destFile = fopen(pathDest, "wb");
        
        if(destFile ==NULL){
            printf("Error opening destination file");
        }else{
    
            while((bytesRead = fread(buffer, 1, sizeof(buffer), sourceFile)) > 0){
                fwrite(buffer, 1, bytesRead, destFile);
            }
            fclose(sourceFile);
            fclose(destFile);
        }
    }
}

void delfile(const char *filePath, const char *file){//Maybe move this to tools
    char path[60]; //Create a string to form the concatanated string with the filename
    char pathTest[60];
    int status;

    strcpy(path, filePath);
    strcat(path, "/");
    strcat(path, file);
    status = remove(path);

    if(status == 0){
        printf("Success: file deleted\n");
    }else{
        printf("Error: file not deleted\n");
        printf("%s", path);
    }
}