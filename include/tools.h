#ifndef TOOLS_H
#define TOOLS_H
#define FILEPATH_LENGTH 1000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void newLineRemove(char *my_str);
size_t readLine(char *rule, FILE *rule_file);
void printToCMD(char *my_str);
void fileDelete(const char *file_path, const char *file);
void fileCopy(const char *file_path, const char *file);
int checkExtension(const char *file_name, const char *extension);
void recursiveLoop(const char *dir_name, const char *search_str, const char option, uint *layer_depth);

#endif