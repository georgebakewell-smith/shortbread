#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void newLineRemove();
void cmdprint(char *myStr);
void delfile(const char *filePath, const char *file);
void copyfile(const char *filePath, const char *file);

#endif