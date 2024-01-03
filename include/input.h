#ifndef INPUT_H
#define INPUT_H

typedef struct {
    size_t num_tokens;
    char command[20];
    char target[20];
}LegInp;

void handleInput(LegInp *leg_input, char *file_path);
int isLegit(char *user_input, LegInp *leg_input);

#endif