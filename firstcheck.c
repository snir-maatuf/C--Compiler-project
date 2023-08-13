#include "firstcheck.h"

#define MAX_LINE 80

/* Skips on word or sequence of non-space characters */
char * skipsOnWORD(char line[],char * ptr){
    while (!isspace(ptr))
    {
        ptr++;
    }
    return ptr;
}


/* Skips on any white space characters*/
char * skipsOnSpaces(char line[],char * ptr){
    while (isspace(ptr))
    {
        ptr++;
    }
    return ptr;
}

/* Initialize address when there have 0 operands */
void zeroOperands(char * line,char * ptr,struct Dcode * dtemp){
    dcurr->ARE = "00";
    strncpy(dcurr->opcode, opcodeToBinary(ptr),4);
    dcurr->opcode[4] = '\0';
    dcurr->destinationType = "000";
    dcurr->sourceType = "000";
}


/* Initialize address when there have 1 operands */
void codingOneOprand(char line[], char * ptr, struct Dcode * dcurr){
    dcurr->ARE = "00";
    strncpy(dcurr->opcode, opcodeToBinary(ptr),4);
    dcurr->opcode[4] = '\0';

    /* skip on first instruction word */
    token = strtok(NULL, delim);
    *ptr=token;
    

    /* check the first operand */
    ptr=skipsOnSpaces(line,ptr);
    ptr=skipsOnWORD(line,ptr);

    memset(dcurr->sourceType,'0',3);
    strncy( dcurr->destinationType ,operandsType(line, ptr, dcurr),3 );
    /* should add a init function that init a label type */
    initOperand(registerBits, ptr, dcurr, isTwoRegisters);

}


/* Initialize address when there have 2 operands */
void codingTwoOprands(char line[], char * ptr, struct Dcode * dcurr){
    int isTwoRegisters = 1;
    char registerBits[3];

    dcurr->ARE = "00";
    
    strncpy(dcurr->opcode, opcodeToBinary(ptr),4);
    dcurr->opcode[4] = '\0';
    
    /* skip on first instruction word */
    token = strtok(NULL, delim);
    *ptr=token;
    

    /* check the first operand */
    ptr=skipsOnSpaces(line,ptr);
    ptr=skipsOnWORD(line,ptr);

    
    if (!isRegister(line,ptr,dcurr) )
    {
        registerBits = operandsType(line, ptr, dcurr);
        /* check the type of the first operand */
        strncy( dcurr->sourceType ,registerBits,3 );
        dcurr->sourceType[3] = '\0';

        initOperand(registerBits, ptr, dcurr, isTwoRegisters);
    }
    else{
        registerBits = operandsType(line, ptr, dcurr);
        strncy( dcurr->sourceType ,registerBits,3 );
        dcurr->sourceType[3] = '\0';

        initOperand(registerBits, ptr, dcurr, isTwoRegisters);
        isTwoRegisters = 0;

    }
    
    ptr=skipsOnWORD(line,ptr);

    while(!isspace(ptr) && ptr != 44){
        ptr++;
    }
    /* skip on comma */
    ptr=skipsOnSpaces(line,ptr);
    ptr=skipsOnWORD(line,ptr);

    if (!isRegister(line,ptr,dcurr) )
    {
        registerBits = operandsType(line, ptr, dcurr);
        /* check the type of the second operand */
        strncy( dcurr->destinationType ,registerBits,3 );
        dcurr->destinationType[3] = '\0';

        initOperand(registerBits, ptr, dcurr, isTwoRegisters);
    } 
    else{ /* split register bits to the struct (2-6 bits)*/
        registerBits = operandsType(line, ptr, dcurr);
        strncy( dcurr->destinationType ,registerBits,3 );

        initOperand(registerBits, ptr, dcurr, isTwoRegisters);
    } 

}


/** 
 * Define instruction name and initialize the binary number
 * to "opcode" by instruction name
 */
void initOpcode(char line[], char * ptr, struct Dcode * dcurr){
    /* initialize the "opcode" bits */
    strncpy(dcurr->opcode, opcodeToBinary(ptr), 4);
    dcurr->opcode[4] = '\0';
}


/* initialize the "source" bits */
void initSource(char line[], char * ptr, struct Dcode * dcurr){
    strncpy(dcurr->sourceType, operandsType(line, ptr, dcurr), 3); /* change the opcodetobinary */
    dcurr->sourceType[3] = '\0';
}


/* initialize the "destination" bits */
void initDestination(char line[], char * ptr, struct Dcode * dcurr){
    strncpy(dcurr->destinationType, opcodeToBinary(ptr), 3);/* error! change the opcodetobinary */
    dcurr->destinationType[3] = '\0';
}


/* Check if the instrunction is address of type 1 */
int isImmediate(char line[], char * ptr){

    if (isdigit(ptr) || ( (ptr==45||ptr==43) && isdigit(ptr++) ))
        {
            return 0;
        }
    return 1;
}


/* Check if the instrunction is address of type 3 */
int isDirective(char line[], char * ptr, struct Dcode * dcurr){

    if (isSymbolExist(ptr))
    {
        return 0;
    }
    
    return 1;
}


/* Check if the instrunction is address of type 5 */
int isRegister(char line[], char * ptr, struct Dcode * dcurr){
    if (ptr == 64 && ptr++ ==114 && ptr+2 >= 48 && ptr+2 <= 55)
    {
        return 0;
    }
    return 1;
}


/* return the register number in char binary number */
char * getRegisterBinaryNumber(char line[], char * ptr, struct Dcode * dcurr){
    if (isRegister)
    {
        return decimalToBinary( atoi(ptr+2) , 3);
    }
    errorsMassages(REGISTER_NOT_EXIST);
    return 0;
}

/* Initialize operand by 1 or 5 address*/
void initOperand(char addressNumber[],char * ptr, struct Dcode * dcurr, int isTwoRegisters ){
    struct  Decode* dnew= NULL;
    dcurr->ARE = "00";
    
    dnew = appendNode(dcurr);
    

    if (strcmp(addressNumber, "001")) 
    {
        if (ptr==43)
        {
            ptr++;
            dnew->binaryNumber = decimalToBinary( atoi(ptr) ,10 );
        }else if (ptr==45)
        {
            ptr++;
            dnew->binaryNumber = decimalToBinary( positiveNumToNegative(atoi(ptr)) ,10 );
        }
        else{
            dnew->binaryNumber = decimalToBinary( atoi(ptr) ,10 );
        }
    }
    else if (strcmp(addressNumber, "101"))
    {
        strncy( dcurr->destinationType ,getRegisterBinaryNumber,3 );

        memset(dcurr->sourceType,'0',2);
        memset(dcurr->opcode,'0',4);
        memset(dcurr->sourceType,'0',3);
        dcurr->destinationType[3] = '\0';

        if (!isTwoRegisters) /* only source register exist */
        {
            dcurr->opcode[2] = '0';
            dcurr->opcode[3] = '0';
            memset(dcurr->destinationType,'0',3);
        }
    } else if (strcmp(addressNumber, "011"))
    {
        /* code */
    }
    
}

/* Define the operand type (1,3,5) */
char * operandsType(char line[], char * token, struct Dcode * dcurr){
    char * ptr = token;
    int bits = 10;
    
    
    if (isImmediate(line, ptr)) /* immediate address */
    {
        return decimalToBinary(1,3);
    }
    else if (isDirective(line,ptr, dcurr))
    {
        return decimalToBinary(3,3);
    }
    else if (isRegister(line, ptr,dcurr)) /* directive register address */
    {
        return decimalToBinary(5,3);
    }
    
    errorsMassages(WRONG_ARGUMENT);

     return '000';
}

/* Convert decimal number to binary according to given number of bits */
char* decimalToBinary(int decimalNum, int limitNumberOFbits) {
    char* binaryString = (char*)malloc(limitNumberOfBits + 1);

    if (binaryString == NULL) {
        /* Memory allocation failed */
        return NULL;
    }

    for (int i = limitNumberOfBits - 1; i >= 0; i--) {
        binaryString[i] = (decimalNum & 1) + 48;
        decimalNum >>= 1;
    }
    free(binaryString);

    return binaryString;
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
    while(isspace(ptr) || ptr != '\t'){
        ptr++;
    }
    /* Skip on spaces and tabs  */
    while(!isspace(ptr) || ptr != '\t'){
        ptr++;
    }
    return ptr;
}


/* Check if the line is symbol and also already in the symbol table */
int isSymbol(char line[], char * ptr, struct symbolTable * shead) {
    char *tmp = (char *)malloc(MAX_LINE * sizeof(char)); 
    char *tmpPtr = tmp; /* Pointer to move through tmp */
    char *linePtr = line; /* Pointer to move through line*/

    while (!isspace(ptr) && (ptr!= 58) ) {
        ptr++;
    }
    
    if (ptr == 58) {
        if(!isSymbolExist(ptr)){
            strcpy(tmp->symbolName,shead);
        }
        else{
            free(tmp);
            return(1);
        }
    }
    
    free(tmp);

    return 0;
}

/* Counting DCstring */
int dcString(char line[] , char * ptr, struct Dcode * dcurr)
{
    struct  Decode* dnew= NULL;
    int dccounter = 0;
    char * binaryPointer;
  
  ptr=skipsOnSpaces(line,ptr);
  if (ptr == 34)
  {
    ptr = ptr + 1;
    while (ptr != 34 && ptr != '\n' )
    {
        if (ptr >= 0 && ptr <=127)
        {
            dnew = appendNode(dtemp);
            strncpy(binaryPointer, decimalToBinary((int)ptr), 12);

            /* Initialize dcode struct */
            initSource(line,ptr,dcurr);
            binaryPointer+=3;
            initOpcode(line,ptr,dcurr);
            binaryPointer+=4;
            initDestination(line,ptr,dcurr);
            binaryPointer+=3;
            strncpy(dcurr->ARE, binaryPointer ,2);
            dcurr->ARE[3] = '\0';

            ptr++;
            dccounter++;
        }
    }
    zeroOperands(line,ptr,dcurr);
  }
  return dccounter + 1;
}


/* Counting DC */
int dcCounter(char line[],char * ptr, struct Dcode * dcurr){
    struct Dcode * dnew = null;
    int count = 1;
    char * binaryString;

    while (ptr!= '\0')
    {
        skipsOnSpaces(line,ptr);
        if (isImmediate(line,ptr))
        {
            dnew = appendNode(dcurr);
            if (ptr=='+')
            {
                ptr++;
                strncpy(binaryString , decimalToBinary(atoi(ptr),10) , 10);
                insert10Bits(dnew, binaryString, 1);

            }else if (ptr=='-')
            {
                ptr++;
                strncpy(binaryString , decimalToBinary(positiveNumToNegative(atoi(ptr)),10) , 10);
                insert10Bits(dnew, binaryString, 0);
            }
            else{
                strncpy(binaryString , decimalToBinary(atoi(ptr),10) , 10);
                insert10Bits(dnew, binaryString, 1);
            }

        }
        
        while(!isspace(ptr) && ptr != 44){
            ptr++;
        }
        skipsOnSpaces(line,ptr);
       if(ptr == 44)
       {
        count++;
        ptr++;
       }
    }
    return count ;
}


/* Split the 10 bits to dcode struct */
void insert10Bits(struct Dcode * dcurr ,char * binaryString, int isMinus){
    if (isMinus)
    {
        dcurr->sourceType = "111";
    }else
    {
        dcurr->sourceType = "000";
    }
    
    dcurr->sourceType[2] = binaryString;
    strncpy(dcurr->opcode, binaryString, 4);
    binaryString+=4;
    strncpy(dcurr->destinationType, binaryString, 3);
    binaryString+=3;
    strncpy(dcurr->ARE, binaryString, 2);
}


/* Convert positive number to negative by 2's complement */
int positiveNumToNegative(int num) {
    const int HexFFFnumber = 0xFFF; /* 0xFFF = 12 bits set to 1 */
    return (HexFFFnumber + 1 - num) & HexFFFnumber;
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
    int tempDC = dc, tempIC = ic, flag, valCounter = 0, tmp1;
    char fileName[MAX_LINE];
    char * ptr, delim = " \t\n,";
    FILE * file;
    char symbolType, *token;
    char line[MAX_LINE] = {'\0'};
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
    while (fgets(line, MAX_LINE, ptr)){
        /* Create a new temp node of decode and also symbolTable node */
        struct  Decode* dtemp= NULL;
        struct  symbolTable* stemp = NULL;
        dtemp = (struct Decode*)malloc(sizeof(struct Decode));
        stemp = (struct symbolTable*)malloc(sizeof(struct symbolTable));
        flag = 1;

        ptr=skipsOnSpaces(line,ptr);

        /* Skip on comment line and empty line */
        if( *line == 59){
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
                if(isSymbolExist(ptr)){
                    break;
                }

                /* Add node to Dcode linkedlist */
                dtemp = appendNode(dhead);

                /* Initialize the node with values */
                strcpy(dtemp -> symbolName, temp->symbolName);
                temp ->address = tempIC;

                /* Add node to symbol table */
                stemp = addInstructionToTable(line,shead);

                /* check which operand source (1,3,5) */

                ptr = skipToInstructType(line,ptr);

                /* Counting the number of the digits */
                tempDC = tempDC + dcCounter(line, ptr);
                tempIC = tempIC + dcCounter(line, ptr);
                
                break;
            
            case 't': /* =string */

                /* check if the symbol is already exist, else break */
                if(isSymbolExist(ptr)){
                    break;
                }
                
                /* Add node to Dcode linkedlist */
                dtemp = appendNode(dhead);

                /* Initialize the node with values */
                strcpy(dtemp -> symbolName, temp->symbolName);
                temp ->address = tempIC;

                /* Add node to symbol table */
                stemp = addInstructionToTable(line,shead);

                ptr = skipToInstructType(line,ptr);

                /* Counting the chars in the string */
                tempDC = tempDC + dcString(line, ptr,dtemp);
                tempIC = tempIC + dcString(line, ptr,dtemp);

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
            stemp = addInstructionToTable(line,shead);
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
            stemp = addInstructionToTable(line,shead);
                break;

            default: /* = code */

            /* check if the symbol is already exist, else break */
            if(isSymbolExist(ptr)){
                break;
            }
            token = strtok(line, delim);
            /* Add node to decode table */
            dtemp = appendNode(dhead);
            temp->ic = tempIC;

            /* Add node to symbol table */
            stemp = addInstructionToTable(line,shead);

            /* Print error if the instruction name is not assembly command */
            if (!isInstructionName(ptr))
            {
                errorMassage(WRONG_INSTRUCTION_NAME);
            }

            *p = token;
            /* define which command group */
            tmp1 = instructionGroup(line,token );
            if ( tmp1 == 1)
            {
                codingTwoOprands(line, ptr, dtemp);
                tempDC+3;

            } else if (tmp1 == 2)
            {
                codingOneOprand(line, ptr, dtemp);
                tempDC+2;

            } else if (tmp1 == 3)
            {
                zeroOperands(line,ptr,dtemp);
                tempDC+1;
            }
            
            /* Counting the number of the data and instruction in the line */
            while (token != NULL) {
                strcat(temp->address, tempIC+1 );
                token = strtok(NULL, delim);
            }

            /* Updating the IC */
            tempIC = temp->ic;

                break;
            }
            
        }
        else{ /* =not a symbol with code */ 

            /* Print error if the instruction name is not assembly command */
            if (!isInstructionName(ptr))
            {
                errorMassage(WRONG_INSTRUCTION_NAME);
            }
            token = strtok(line, delim);

            *p = token;
            /* define which command group */
            tmp1 = instructionGroup(line,token );
            if ( tmp1 == 1)
            {
                codingTwoOprands(line, ptr, dtemp);
                tempDC+3;

            } else if (tmp1 == 2)
            {
                codingOneOprand(line, ptr, dtemp);
                tempDC+2;

            } else if (tmp1 == 3)
            {
                zeroOperands(line,ptr,dtemp);
                tempDC+1;
            }


            if(isInstructionName(ptr)){
                valCounter = dcCounter(line,ptr ) + dcString(line, ptr,dtemp);

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

