#include <stdio.h>
#include <stdlib.h>
#include "../include/tools.h"
#include "../include/input.h"
#include "../include/commands.h"

void excommand(LegInp *pLegInp, const char *filePath){
    
    if(strcmp(pLegInp->command,"list")==0){
        listfiles(filePath);
    }else if(strcmp(pLegInp->command,"delete")==0){
        delfile(filePath, pLegInp->target);
    }else if(strcmp(pLegInp->command,"copy")==0){
        copyfile(filePath, pLegInp->target);
    }else if(strcmp(pLegInp->command,"autorun")==0){
        autorun(filePath);
    }else if(strcmp(pLegInp->command,"prule")==0){
        printrules();
    }else if(strcmp(pLegInp->command,"arule")==0){
        addrule();
    }
    else{
        printf("Please enter a valid command");
    }
    //elseif for additional commands
}