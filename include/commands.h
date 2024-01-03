#ifndef COMMANDS_H
#define COMMANDS_H

void listfiles(const char *dir_name, const char *search_str, const char option);
void commandDelete(const char *file_path, const char *target);
void commandCopy(const char *file_path, const char *target, const char *dest_path);
void autorun(const char *file_path);
void printrules();
void addrule();
void ruleAlter(const char option);

#endif