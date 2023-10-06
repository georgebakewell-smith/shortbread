#ifndef INPUT_H
#define INPUT_H

typedef struct {
    size_t numTokens;
    char command[20];
    char target[20];
}leginp;

void handleInput(leginp *pLegInp, char *filePath);

#endif