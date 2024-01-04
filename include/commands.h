#ifndef COMMANDS_H
#define COMMANDS_H


void commandDelete(const char *file_path, const char *target);
void commandCopy(const char *file_path, const char *target, const char *dest_path);
void loopFiles(const char *dir_name, const char *search_str, const char option);
void autoRun(const char *file_path);
void rulePrint();
void ruleAdd();
void ruleAlter(const char option);

#endif