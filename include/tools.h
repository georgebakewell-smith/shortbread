#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void newLineRemove(char *my_str);
size_t readLine(char *rule, FILE *rule_file);
void cmdprint(char *my_str);
void delfile(const char *file_path, const char *file);
void copyfile(const char *file_path, const char *file);
int checkExtension(const char *file_name, const char *extension);

#endif