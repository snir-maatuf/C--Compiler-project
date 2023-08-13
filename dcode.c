#include "dcode.h"


/*Returns the opcode number of the instructions as a binary number*/
char* opcodeToBinary(char *ptr) 
{
    char *p;
    char tmp[5];
    
    strcpy(tmp, "0000");
    if(!strcmp(ptr, "mov"))
        strcpy(tmp,"0000");
    else if(!strcmp(ptr, "cmp"))
        strcpy(tmp,"0001");
    else if(!strcmp(ptr, "add"))
        strcpy(tmp,"0010");
    else if(!strcmp(ptr, "sub"))
        strcpy(tmp,"0011");
    else if(!strcmp(ptr, "not"))
        strcpy(tmp,"0100");
    else if(!strcmp(ptr, "clr"))
        strcpy(tmp,"0101");
    else if(!strcmp(ptr, "lea"))
        strcpy(tmp,"0110");
    else if(!strcmp(ptr, "inc"))
        strcpy(tmp,"0111");
    else if(!strcmp(ptr, "dec"))
        strcpy(tmp,"1000");
    else if(!strcmp(ptr, "jmp"))
        strcpy(tmp,"1001");
    else if(!strcmp(ptr, "bne"))
        strcpy(tmp,"1010");
    else if(!strcmp(ptr, "red"))
        strcpy(tmp,"1011");
    else if(!strcmp(ptr, "prn") )
        strcpy(tmp,"1100");
    else if(!strcmp(ptr, "jsr"))
        strcpy(tmp,"1101");
    else if(!strcmp(ptr, "rts"))
        strcpy(tmp,"1110");
    else if(!strcmp(ptr, "stop"))
        strcpy(tmp,"1111");
    p = tmp;
    return p;
}

/* Define the instruction group  */
int instructionGroup(char line[], char * p)
{
  if(!strcmp(line, "mov") ||!strcmp(line, "cmp")|| !strcmp(line, "add")||!strcmp(line, "sub")|| !strcmp(line, "lea"))
    return 1;
  else
  if(!strcmp(line, "not") || !strcmp(line, "clr") || !strcmp(line, "bne") || !strcmp(line, "dec")||
         !strcmp(line, "inc")|| !strcmp(line, "jmp")|| !strcmp(line, "red")|| !strcmp(line, "prn")|| !strcmp(line, "jsr"))
    return 2;
  else
  if(!strcmp(line, "rts") || !strcmp(line, "stop"))
    return 3;

  return -1;
}

/* Add node the the dcode table */
Dcode * appendNode(struct Dcode * dcurr )
{
    struct  Decode* newNode= NULL;

    while (dcurr->next != NULL) {
            dcurr = dcurr->next;
    }

    /* Add the new node to the end */
    dcurr->next = newNode;
    
    return newNode;
}
