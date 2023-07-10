#include "firstcheck.h"

/* chack the excactly type of instructions (Like: instruction start in point "." and more...) */

/* func that runs on each line the next code: */
/* isSymbol || entern&extern || string&data */

/* call to dcode functions from dcode.h */

int stringORdata();

whichOpcode(char line[], char * ptr, struct Dcode * dcurr){

    strcpy(dcurr->opcode , opcodeToBinary(ptr));
}


int isImmediate(char line[], char * ptr){
    /* add line of binary */

}
int isDirective(char line[], char * ptr){

}
int isRegister(char line[], char * ptr){

}


/* Define and initialize the address destination */
whichDestination(char line[], char * ptr, struct Dcode * dcurr){
    char tempLine[MAX] = {'\0'};
    
    if (isImmediate())
    {
        /* code */
    }
    else if (isDirective())
    {
        /* code */
    }else if (isRegister())
    {
        /* code */
    }
    

    while (isspace(line[ptr]))
    {
        ptr++;
    }
     
}

/* Recognize if the given command is assembly command */
int isInstructionName(char * ptr){

    int i;
    char *token;
    token = strtok(ptr, " \t");
        
    /* Check if the instruction command is correct */
    for ( i = 0; i < sizeof(instructionsNames) / sizeof(instructionsNames[0]); i++)
     {
        if (strcmp(token, instructionsNames[i]) == 0)
        {
            return 0;
        }
     }

    /* Instruction is not correct */
    return 1;
}



/* Skip on chars until instruction type */
char * skipToInstructType( char line[], char * ptr){

    /* Skip on the symbol text */
    while(isspace(line[ptr]) || line[ptr] != '\t'){
        ptr++;
    }
    /* Skip on spaces and tabs  */
    while(!isspace(line[ptr]) || line[ptr] != '\t'){
        ptr++;
    }
    return ptr;
}

/* Check if the given symbol is already in the symbol table */
int isSymbolExist(struct symbolTable head,const char* ptr){
    struct symbolTable* curr = head;

    while (curr != NULL) {
        if (strcmp(curr->name, name) == 0) {
            return 1; /* Symbol exists */
        }
        curr = curr->next;
    }

    free(curr)
    return 0;
}


/* Check if the line is symbol and also already in the symbol table */
int isSymbol(char line[], char *ptr, struct symbolTable *shead) {
    char *tmp = malloc(MAX * sizeof(char)); 
    char *tmpPtr = tmp; /* Pointer to move through tmp */
    char *linePtr = line; /* Pointer to move through line*/

    while (!isspace(*linePtr) && *linePtr != ':') {
        *tmpPtr = *linePtr;
        tmpPtr++;
        linePtr++;
    }
    
    if (*linePtr == ':') {
        if(isSymbolExist(shead,ptr)){
            strcpy(temp->symbol,sname);
        }
        else{
            free(tmp);
            return(1);
        }
    }
    
    /* Cleanup and free allocated memory */
    free(tmp);

    /*Return a value (replace with appropriate return statement)*/
    return 0;
}

/* Counting DCstring */
int dcString(char line[] , int index)
{
  int dccounter = 0;
  while(isspace(line[index]))
    index ++;
  if (line[index] == 34)
  {
    index = index + 1;
    while (line[index] != 34 && line[index] != '\n' )
    {
      index++;
      dccounter++;
    }
  }
  return dccounter + 1;
  
}
 
/* Counting DC*/
int dcCounter(char line[], int i){
    int count = 1;

    while (line[i] != '\0')
    {
       if(line[i] == 44)
         count++;
          i++;
    }
    return count ;
}


char *skipSpacesAndTabs(char *str) {
    while (*str == ' ' || *str == '\t') { /* recognize space or tab */
        str++; /* skip the space or tab */
    }
    return str;
}

/* Return line without spaces and tabs */
void removeSpacesAndTabs(char *line) {
    int i, count =0;
    
    for (i = 0; line[i] != 'ֿֿֿֿֿֿ\0'; i++) {
        if (!isspace((char)line[i]) && line[i] != '\t' && line[i] != '\n') {
            line[count++] = line[i];
        }
    }
    line[count] = '\0';
}

/* This func goin though on the all lines in the file */
int firstCheck(int fileIndex, char *argv[], struct symbolTable shead, struct Decode dhead, int ic, int dc){
    int tempDC = dc, tempIC = ic, flag, valCounter = 0;
    char fileName[MAX];
    char * ptr, delim = " \t\n,";
    FILE * file;
    char symbolType, *token;
    char line[MAX] = {'\0'};
    struct  symolTable* syCurr= NULL;
    struct  Decode* dCurr= NULL;
    struct  Decode* dtail= NULL;
    

    /* Create new decode NODE and symbol table NODE */
    syCurr = (struct symbolTable*)malloc(sizeof(struct symbolTable));
    dCurr = (struct Decode*)malloc(sizeof(struct Decode));

    /* initialize fileName by strcpy func */
    sprintf(fileName, "%s.am", argv[fileIndex]);

    file = fopen(fileName, 'r');
    if (file == NULL)
    {
        printf("Error! Can't opening file: %s\n", file);
    }


    /* Read each line and */
    while (fgets(line, MAX, ptr)){
        /* Create a new temp node of decode and also symbolTable node */
        struct  Decode* dtemp= NULL;
        struct  symbolTable* stemp = NULL;
        dtemp = (struct Decode*)malloc(sizeof(struct Decode));
        stemp = (struct symbolTable*)malloc(sizeof(struct symbolTable));
        flag = 1;

        ptr = skipSpacesAndTabs(ptr);

        /* Skip on comment line and empty line */
        if( *line == ';' ){
            ptr++;
            continue;
        }

        /* check data or string*/
        flag = isSymbol(line,ptr, shead); /* Need to add if its not symbol (what it do?)*/
        if (flag)
        {
            /* Return the second chr from the current instruct name, else return null */
            symbolType = getSymbolChr(skipToInstructType(line, ptr));
        }
        
        
        /* Check extrn or entrny, else return null */
        if ( getSymbolChr(ptr) == 'e')
        {
            symbolType = 'x';
        }
        else {
            symbolType = 'n';
        }
        
         

        if ( flag || symbolType)
        {
            switch (symbolType)
            {
            case 'a': /* =data */
                
                /* check if the symbol is already exist, else break */
                if(!isSymbolExist){
                    break;
                }

                /* Add node to Dcode linkedlist */
                dhead->next = dtemp;
                dhead =  dhead->next;

                /* Initialize the node with values */
                strcpy(dtemp -> symbolName, temp->symbolName);
                temp ->address = tempIC;

                /* Add node to symbol table */
                shead->next = temp;
                shead =  shead->next;

                /* check which operand source (1,3,5) */

                ptr = skipToInstructType(line,ptr);

                /* Counting the number of the digits */
                tempDC = tempDC + dcCounter(line, ptr);
                tempIC = tempIC + dcCounter(line, ptr);
                
                break;
            
            case 't': /* =string */

                /* check if the symbol is already exist, else break */
                if(!isSymbolExist){
                    break;
                }
                
                /* Add node to Dcode linkedlist */
                dhead->next = dtemp;
                dhead =  dhead->next;

                /* Initialize the node with values */
                strcpy(dtemp -> symbolName, temp->symbolName);
                temp ->address = tempIC;

                /* Add node to symbol table */
                shead ->next = temp;
                shead =  shead->next;

                ptr = skipToInstructType(line,ptr);

                /* Counting the chars in the string */
                tempDC = tempDC + dcString(line, ptr);
                tempIC = tempIC + dcString(line, ptr);

                break;

            case 'n': /* =entry*/
            /* Pointing on .entry */
            token = strtok(line, delim);

            if (token)
            {
                strcat(temp->value, token);
                /* Jump to the second string */
                token = strtok(NULL, delim);
        
                if (token){
                    strcat(temp->address, tempIC+1 );
                }
            }
            shead->next = temp;
            shead = shead->next;
                /* code */
                break;
                
            case 'x': /* =extern*/
            /* Pointing on .extern */
            token = strtok(line, delim);

            if (token)
            {
                strcat(temp->value, token);
                /* Jump to the second string */
                token = strtok(NULL, delim);
        
                if (token){
                    strcat(temp->address, tempIC+1 );
                }
            }
            shead->next = temp;
            shead = shead->next;
                break;

            default: /* = code */

            /* check if the symbol is already exist, else break */
            if(!isSymbolExist){
                break;
            }
            token = strtok(line, delim);
            
            
            /* Add node to Dcode linkedlist */
            dhead->next = dtemp;
            dhead =  dhead->next;

            /* Initialize the node with values */
            strcpy(dtemp -> symbolName, ".code");
            temp ->address = tempIC;

            /* Add node to symbol table */
            shead ->next = temp;
            shead =  shead->next;

            /* Print error if the instruction name is not assembly command */
            if (!isInstructionName(ptr))
            {
                errorMassage(WRONG_INSTRUCTION_NAME);
            }
            
            /* consider to initialize ARE to 00 */

            whichOpcode(char line[], char * ptr, struct Dcode * dcurr);
            whichDestination(char line[], char * ptr, struct Dcode * dcurr);
             
            /* Counting the number of the data and instruction in the line */
            while (token != NULL) {
                strcat(temp->address, tempIC+1 );
                token = strtok(NULL, delim);
            }

            /* Updating the IC */
            tempIC = temp->address;

                break;
            }
            
        }
        else{ /* =not a symbol */ 

            if(isInstructionName(ptr)){
                valCounter = dcCounter() + dcString();

                /* should be here the declaration of struct */

                if( valCounter > 0 ){
                    tempDC = tempDC + valCounter;
                    tempIC = tempIC + valCounter;
                }

            }
        }
        
        /* ... (All the function on each line ) */
    }

    fclose(fileName);

    /* initialize NULL for decode linkedlist */
    dtail = (struct Decode*)malloc(sizeof(struct Decode));
    dhead ->next = dtail;

    ic = tempIC;
    dc = tempDC;
    

    return flag; 
}

