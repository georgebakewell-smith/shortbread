#ifndef INPUT_H
#define INPUT_H

typedef struct {
    size_t numTokens;
    char command[20];
    char target[20];
}LegInp;

void handleInput(LegInp *pLegInp, char *filePath);
int isLegit(char *userInput, LegInp *pLegInp);

#endif