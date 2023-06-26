#include "firstcheck.h"

/* chack the excactly type of instructions (Like: instruction start in point "." and more...) */

/* func that runs on each line the next code: */
/* isSymbol || enctern&extern || string&data */

/* call to dcode functions from dcode.h */

int stringORdata();

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


/* should check if the symbol is already in the symbol table */
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
    }
    
    // Cleanup and free allocated memory
    free(tmp);

    // Return a value (replace with appropriate return statement)
    return 0;
}

/* Counting DCstring */
int dcString(char line[] , int index, struct  Decode* dhead)
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
int firstCheck(int fileIndex, char *argv[], struct symbolTable shead, struct Decode dhead){
    int tempDC = 0, tempIC = 100, flag, valCounter = 0;
    char fileName[MAX];
    char * ptr, delim = " \t\n";
    FILE * file;
    char symbolType, *token;
    char line[MAX] = {'\0'};
    struct  symolTable* syCurr= NULL;
    struct  Decode* dCurr= NULL;

    

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

        
        flag = isSymbol(line,ptr, shead); /* Need to add if its not symbol (what it do?)*/
        
        /* Return the second chr from the current instruct name */
        symbolType = getSymbolChr(ptr);

        

        if ( isSymbol(line,ptr, shead) || symbolType )
        {
            switch (symbolType)
            {
            case 'a': /* =data */
                /* Add node to Dcode linkedlist */
                dhead->next = dtemp;
                dhead =  dhead->next;

                /* Initialize the node with values */
                strcpy(dtemp -> symbolName, temp->symbolName);
                temp ->address = tempIC;

                /* Add node to symbol table */
                shead ->next = temp;
                shead =  shead->next;

                /* Skip on the .data text */
                while(isspace(line[ptr]) || line[ptr] != '\t'){
                    ptr++;
                }
                /* Skip on spaces and tabs  */
                while(!isspace(line[ptr]) || line[ptr] != '\t'){
                    ptr++;
                }
                
                tempDC = tempDC + dcCounter(line, ptr);
                tempIC = tempIC + dcCounter(line, ptr);
                
                break;
            
            case 't': /* =string */
                
                /* code */
                break;
            case 'o': /* = code */
                /* code */
                break;
            case 'n': /* =entry*/ MAIN:
                /* code */
                break;
            case 'x': /* =extern*/

                token = strtok(NULL, delimiters);

                if (token) {
                    /* Skip on the second token */
                    token = strtok(NULL, delimiters);
                    if (token) {
                        strcpy(temp->symbol, token);

                        /* Copy the symbol name until the end of line */
                        while ((token = strtok(NULL, ""))) {
                            strcat(temp->symbol, " ");
                            strcat(temp->symbol, token);
                        }
                    }
                }
                
                break;
            case '\0': /* =isSymbol*/
                /* code */
                break;

            default:
                break;
            }
            /* code */
        }
        else{
            valCounter = dcCounter() + dcString() ;

            if( valCounter > 0 ){
                tempDC = tempDC + valCounter;
                tempIC = tempIC + valCounter;
            }
        }
        
        /* ... (All the function on each line ) */
    }
    fclose(file);

    return flag; 
}

