#include <stdio.h>
#include <stdlib.h>
#include "../include/tools.h"
#include "../include/input.h"
#include "../include/commands.h"

void executeCommand(LegInp *leg_input, const char *file_path){
    
    if(strcmp(leg_input->command,"list")==0){
        loopFiles(file_path, "", 'p');
    }else if(strcmp(leg_input->command,"delete")==0){
        commandDelete(file_path, leg_input->target);
    }else if(strcmp(leg_input->command,"copy")==0){
        commandCopy(file_path, leg_input->target);
    }else if(strcmp(leg_input->command,"autorun")==0){
        autoRun(file_path);
    }else if(strcmp(leg_input->command,"prule")==0){
        rulePrint();
    }else if(strcmp(leg_input->command,"arule")==0){
        ruleAdd();
    }else if(strcmp(leg_input->command,"drule")==0){
        printf("delete rule\n");
        ruleAlter('d');
    }else if(strcmp(leg_input->command,"erule")==0){
        ruleAlter('e');
    }else if(strcmp(leg_input->command,"pcdir")==0){
        cDirAlter('p');
    }else if(strcmp(leg_input->command,"ecdir")==0){
        cDirAlter('e');
    }
    else{
        printf("\nPlease enter a valid command");
    }
    //elseif for additional commands
}