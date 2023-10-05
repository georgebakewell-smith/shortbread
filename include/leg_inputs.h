#ifndef __LEG_INPUTS_H
#define __LEG_INPUTS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LegInputs{
    size_t numTokens;
    char command[20];
    char target[20];
}leginp;

#endif