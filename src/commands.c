#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "../include/input.h"
#include "../include/tools.h"
#include "../include/commands.h"

void listfiles(const char *dirname){
    //Opens directory
    DIR *dir = opendir(dirname);
    if(dir == NULL){
        printf("Directory not opened\n");
    }
    
struct dirent *entity;
entity = readdir(dir);
//Cycles through contents
printf("\n");
while(entity != NULL){
    if(entity->d_type == DT_REG){
        printf("%s", entity->d_name);printf("\n");
        
    }
    //Calls listfiles() within itself to recursively access folders within
    if(entity->d_type == DT_DIR && strcmp(entity->d_name, ".")!=0 && strcmp(entity->d_name, "..")!=0){
        char path[100] = {0};
        strcat(path, dirname);
        strcat(path, "/");
        strcat(path, entity->d_name);
        listfiles(path);
    }   
    entity = readdir(dir);
}
    closedir(dir);
}


void copyfile(const char *filePath){
    unsigned char buffer[1024];
    size_t bytesRead;
    FILE *sourceFile, *destFile;
    sourceFile = fopen("testfile.txt", "rb");
    destFile = fopen("copy.txt", "wb");
    if(sourceFile == NULL || destFile ==NULL){
            printf("Error opening fiels\n");
    }
   
    while((bytesRead = fread(buffer, 1, sizeof(buffer), sourceFile)) > 0){
        fwrite(buffer, 1, bytesRead, destFile);
    }

    fclose(sourceFile);
    fclose(destFile);
}

void delfile(const char *filePath, const char *file){//Maybe move this to tools
    char path[60]; //Create a string to form the concatanated string with the filename
    char pathTest[60];
    int status;

    FILE *fptr;
    // Create the file for testing so don't have to add deleted file each time
    strcpy(pathTest, filePath);
    strcat(pathTest, "/");
    strcat(pathTest, file);
    fptr = fopen(pathTest, "w");
    // Close the file
    fclose(fptr);

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