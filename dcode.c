


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
const char* instructionGroup(char line[], char * p)
{
  char *p;
  char new[5];
  memset(new , '\0' , 5);
  if(!strcmp(op, "add") || !strcmp(op, "clr") || !strcmp(op, "jmp"))
    strcpy(new,"1010");
  else
  if(!strcmp(op, "sub") || !strcmp(op, "not") || !strcmp(op, "bne"))
    strcpy(new,"1011");
  else
  if(!strcmp(op, "inc") || !strcmp(op, "jsr"))
    strcpy(new,"1100");
  else
  if(!strcmp(op, "dec"))
    strcpy(new,"1101");
  else
    strcpy(new,"0000");
 p = new;
  return p;
}
