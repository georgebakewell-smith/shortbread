#include <stdio.h>
#include <stdlib.h>
#include "../include/tools.h"
#include "../include/input.h"
#include "../include/commands.h"

void excommand(leginp *pLegInp, char *filePath){
    
    if(strcmp(pLegInp->command,"list")==0){
        listfiles(filePath);
    }else if(pLegInp->command,"list"){
        delhandle(filePath, pLegInp->target);
    }//elseif for additional commands
}