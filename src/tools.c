#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/tools.h"


size_t readLine(char *rule, FILE *rule_file){
    char line[100];
    if(fgets(line, 100, rule_file) != NULL){
        strcpy(rule, line);
        newLineRemove(rule);
        return 0;
    }   else{
        strcpy(rule, line);
        newLineRemove(rule);
        return 1;
    }    
}

void newLineRemove(char *my_str){
    size_t input_length;
    input_length = strlen(my_str);
        *(my_str+input_length-1) = '\0';
}

void cmdprint(char *my_str){
    printf("\n%s$", my_str);
}

void copyfile(const char *file_path, const char *file){
    unsigned char buffer[1024];
    size_t bytes_read;
    FILE *source_file, *dest_file;
    //Create full filepath with filePath and target file
    //Should probably create function for this and add to tools
    char source_path[100], dest_path[100];
    strcpy(source_path, file_path);
    strcat(source_path, "/");
    strcat(source_path, file);
    strcpy(dest_path, "/home/george/Documents/cprojects/copiedfiles");
    strcat(dest_path, "/");
    strcat(dest_path, file);
    
    source_file = fopen(source_path, "rb");
    
        if(source_file == NULL){
                printf("Error opening source file\n");
                
        }else{
            dest_file = fopen(dest_path, "wb");
        
        if(dest_file ==NULL){
            printf("Error opening destination file");
        }else{
    
            while((bytes_read = fread(buffer, 1, sizeof(buffer), source_file)) > 0){
                fwrite(buffer, 1, bytes_read, dest_file);
            }
            fclose(source_file);
            fclose(dest_file);
        }
    }
}

void delfile(const char *file_path, const char *file){//Maybe move this to tools
    char path[100]; //Create a string to form the concatanated string with the filename
    int status;

    strcpy(path, file_path);
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

int checkExtension(const char *file_name, const char *extension){
    // Compares a filename with a given extension
    int index = -1;
    
    // Finds index of final '.' character in the file name, if any
    for(int i = 0; i < strlen(file_name); i++){
        if(file_name[i] == '.'){
            index = i;
        }
    }

    // Checks if there was a '.' and compares the extensions
    if(index == -1){
        printf("The file does not have an extension.\n");
        return -1;
    }else{
        return strcmp(&file_name[index], extension);
    }
    
}