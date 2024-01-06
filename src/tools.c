#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "../include/tools.h"

size_t readLine(char *rule, FILE *rule_file){
    // Takes a line from a file and saves to a string

    char line[100];
    if(fgets(line, 100, rule_file) != NULL){
        // Saves each line to string
        strcpy(rule, line);
        newLineRemove(rule);
        return 0;
    }   else{
        // End of file
        return 1;
    }    
}

void newLineRemove(char *my_str){
    // Takes a string obtained from fgets and replaces \n with \0
    size_t input_length;
    input_length = strlen(my_str);
        *(my_str+input_length-1) = '\0';
}

void printToCMD(char *my_str){
    // Prints to the command line a string on the next line down
    printf("\n%s$", my_str);
}

void fileCopy(const char *file_path, const char *file){
    // Copys an individual file to the location specified in assets/destination_filepath.txt

    unsigned char buffer[1024];
    size_t bytes_read;
    FILE *source_file, *dest_file, *dest_path_file;
    char dest_path[FILEPATH_LENGTH], source_path[FILEPATH_LENGTH];
    char dest_path_filename[] = "./assets/destination_filepath.txt";   
    dest_path_file = fopen(dest_path_filename, "r");
    
    // Takes destination filepath from destination_filepath.txt
    if(dest_path_file != NULL){
        
        fgets(dest_path, FILEPATH_LENGTH, dest_path_file);
        newLineRemove(dest_path);
        fclose(dest_path_file);
        
    }else{
        printf("Error opening location of destination file address.\n");
    }

    //Create full filepath with filePath and target file
    strcpy(source_path, file_path);
    strcat(source_path, "/");
    strcat(source_path, file);
    strcat(dest_path, "/");
    strcat(dest_path, file);
    
    source_file = fopen(source_path, "rb");
    
        if(source_file == NULL){
                printf("Error opening source file\n");
                
        }else{
            // Opens blank destination file
            dest_file = fopen(dest_path, "wb");
        
        if(dest_file ==NULL){
            printf("Error opening destination file\n");
        }else{
            // Copies in binary mode the file from source to the blank destination file
            while((bytes_read = fread(buffer, 1, sizeof(buffer), source_file)) > 0){
                fwrite(buffer, 1, bytes_read, dest_file);
            }
            printf("Success: file '%s' copied\n", file);
            fclose(source_file);
            fclose(dest_file);
        }
    }
}

void fileDelete(const char *file_path, const char *file){
    // Deletes an individual file

    char path[FILEPATH_LENGTH]; //Create a string to form the concatanated string with the filename
    int status;

    // Formats the filepath then removes
    strcpy(path, file_path);
    strcat(path, "/");
    strcat(path, file);
    status = remove(path);

    // Checks if remove was successful
    if(status == 0){
        printf("Success: file '%s' deleted\n", file);
    }else{
        printf("Error: file not deleted\n");
        printf("%s", path);
    }
    
}

int checkExtension(const char *file_name, const char *extension){
    // Compares a filename with a given extension

    int index = -1;
    
    // Finds index of final "." character in the file name, if any
    for(int i = 0; i < strlen(file_name); i++){
        if(file_name[i] == '.'){
            index = i;
        }
    }

    // Checks if there was a '.' and compares the extensions
    if(index == -1){
        return -1;
    }else{
        return strcmp(&file_name[index], extension);
    }
    
}

void recursiveLoop(const char *dir_name, const char *search_str, const char option, uint *layer_depth){
    // Loops recursively through a directory and can either print, delete or copy files according to some condition

    //Opens directory
    DIR *dir = opendir(dir_name);
    if(dir == NULL){
        printf("Directory not opened\n");
    }
    
    struct dirent *entity;
    entity = readdir(dir);
    //Cycles through contents, and either prints, or checks condition and deletes/copys
    while(entity != NULL){
        if(entity->d_type == DT_REG){
            if(option == 'p'){
                for(int i = 0; i < *layer_depth; i++){printf("\t");}
                printf("%s", entity->d_name);printf("\n");
            }else if(option == 'c' && checkExtension(entity->d_name, search_str) == 0){
                fileCopy(dir_name, entity->d_name);
            }
            else if(option == 'd' && checkExtension(entity->d_name, search_str) == 0){
                fileDelete(dir_name, entity->d_name);
            }
            
            
        }
        // If a directory is found calls listfiles() within itself to recursively access folders within
        if(entity->d_type == DT_DIR && strcmp(entity->d_name, ".")!=0 && strcmp(entity->d_name, "..")!=0){
            if(option == 'p'){
                for(int i = 0; i < *layer_depth; i++){printf("\t");}
                printf("----%s----", entity->d_name);printf("\n");
            }
            else if(option == 'c' && checkExtension(entity->d_name, search_str) == 0){
                fileCopy(dir_name, entity->d_name);
            }
            else if(option == 'd' && checkExtension(entity->d_name, search_str) == 0){
                fileDelete(dir_name, entity->d_name);
            }
            
            // Saves to a different pointer the filepath of the directory within the initial directory
            char path[FILEPATH_LENGTH] = {0};
            strcat(path, dir_name);
            strcat(path, "/");
            strcat(path, entity->d_name);
            *layer_depth = *layer_depth + 1;
            recursiveLoop(path, search_str, option, layer_depth);
            *layer_depth = *layer_depth - 1;
        }   
        entity = readdir(dir);
    }
    closedir(dir);
    
}