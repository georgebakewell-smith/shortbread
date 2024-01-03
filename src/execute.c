#include <stdio.h>
#include <stdlib.h>
#include "../include/tools.h"
#include "../include/input.h"
#include "../include/commands.h"

void excommand(LegInp *leg_input, const char *file_path){
    
    if(strcmp(leg_input->command,"list")==0){
        listfiles(file_path, "", 'p');
    }else if(strcmp(leg_input->command,"delete")==0){
        commandDelete(file_path, leg_input->target);
    }else if(strcmp(leg_input->command,"copy")==0){
        commandCopy(file_path, leg_input->target, "/home/george/Documents/cprojects/copiedfiles");
    }else if(strcmp(leg_input->command,"autorun")==0){
        autorun(file_path);
    }else if(strcmp(leg_input->command,"prule")==0){
        printrules();
    }else if(strcmp(leg_input->command,"arule")==0){
        addrule();
    }else if(strcmp(leg_input->command,"drule")==0){
        ruleDelete();
    }
    else{
        printf("Please enter a valid command");
    }
    //elseif for additional commands
}