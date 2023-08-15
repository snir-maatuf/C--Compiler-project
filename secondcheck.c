#include "secondcheck.h"
#include "firstcheck.h"


#define MAX_LINE 80
#define MAX_LABLE 31


/* Returns the number of the numbers  */
int numbersCounter(char line[], char * ptr){
    int count;

    while(!isspace(ptr) && ptr != 44){
        ptr++;
        }
                
    skipsOnSpaces(line,ptr);

    if(ptr == 44)
    {
        count++;
        ptr++;
    }
    return count;
}


/* Returns the number of the chars  */
int charsCounter(char line[], char * ptr){
    int counter = 0;
  

    if (ptr == 34)
    {
        ptr = ptr + 1;
        while (ptr != 34 && ptr != '\n' )
        {
            /* Only chars acceptable */
            if ( (ptr >= 65 && ptr <=90) || (ptr >= 97 && ptr <=122) ) 
            {
                ptr=skipsOnSpaces(line,ptr);
                ptr++;
                counter++;
            }
        }
    }
    return counter;
}


/* Convert binary string to BASE 64 style */
char Base64Converter(char *binaryNum) {

    /* extract the first 6 and last 6 digits to binary number */
    char firstSix[7], lastSix[7], label[2];
    int firstValue, lastValue;
    char * p;

    strncpy(firstSix, binaryNum, 6);
    firstSix[6] = '\0';
    strncpy(lastSix, binaryNum + 6, 6);
    lastSix[6] = '\0';

    /* convert binary digits (as chars) to decimal values */
    firstValue = strtol(firstSix, NULL, 2);
    lastValue = strtol(lastSix, NULL, 2);

    /* convert decimal values to base-64 characters using the "base64" */
    label[0] = BASE64[firstValue];
    label[1] = BASE64[lastValue];
    label[2] = '\0';

    p = label[0];

    return p;

}



/* This func goin though on the all lines in the file */
int secondCheck(int fileIndex, char *argv[], struct symbolTable *shead, struct Decode *dhead, int ic, int dc){
    char fileName[MAX_LINE];
    int number[MAX_LINE];
    char binaryNum[2];
    int tmpArray[12];
    FILE * file;
    FILE * fixedfile;
    char * ptr;
    char line[MAX_LINE] = {'\0'};
    char fname[MAX_LINE];
    char fname2[MAX_LINE];
    int lineLength,i=0 ,amountOFnumbers, isErrorFlag = 0, isMinus=0,amountOFchars;
    char symbolType;
    char symbol[MAX_LABLE];
    ic=100;
    struct symbolTable *stemp= NULL;
    stemp = (struct symbolTable*)malloc(sizeof(symbolTable));



    memset(symbol, '\0');
    strcpy(fileName, argv[fileIndex]);
    strncat(fileName, ".am", 3);
    strcpy(fname2, argv[fileIndex]);
    strncat(fname2, ".ob", 3);

    file = fopen(fileName, 'r');
    if (file == NULL)
    {
        printf("Error! Can't opening file: %s\n", file);
    }

    fixedfile = fopen(fname2, "w");
    if (fpr == NULL)
    {
        printf("Can't open the file: %s \n \n", argv[i]);
        return 1;
    }
    fprintf(fixedfile , "   %d %d \n",ic - dc -100 , dc);

    

    while (fgets(line, MAX_LINE, file)){
        ptr=skipsOnSpaces(line,ptr);
        

        if (isSymbolExist(ptr) )
        {
            /* skipping on instruction word */
            ptr=skipsOnWORD(line,ptr);
            ptr=skipsOnSpaces(ptr); 
            
            symbolType = getSymbolChr(ptr);
            if (symbolType == 'a') /* = data(numbers) */
            { 
                ptr=skipsOnWORD(ptr);
                ptr=skipsOnSpaces(ptr);

                /*pointing on first number*/
                amountOFnumbers = numbersCounter(line,ptr);
                for ( i = 1; i < amountOFnumbers; i++)
                {
                    memset(number, '\0' , MAX_LINE);
                    
                    if (ptr == 45 )
                    {
                        isMinus = 1; 
                        ptr++;
                    }
                    
                    else if (ptr == 43 ){
                        ptr++;
                    }

                    if(ptr > 47 && ptr < 58)
                    {
                        strcpy(number, atoi(ptr));
                        ptr++;
                    }

                    if (atoi(number) != 0){
                        if (isMinus)
                        {
                            /* Add address label to obj file */
                            strncpy(binaryNum,Base64Converter( decimalToBinary( positiveNumToNegative(atoi(ptr)) ,12)),2);
                            ic++;
                        }
                        else
                        {
                            strncpy(binaryNum,Base64Converter( decimalToBinary( atoi(ptr) ,12) ), 2);
                            ic++;
                        }

                        
                        fprintf(fixedfile,'0%d %c',ic, binaryNum);
                        ptr++;

                    }
                }
                
                

            }else if (symbolType == 't') /* = string */
            {
                /* skipping on instruction word */
                ptr=skipsOnWORD(ptr);
                ptr=skipsOnSpaces(ptr);

                amountOFchars = charsCounter(line,ptr);
                /* Convert the chars to BASE64 and add them to file */
                for ( i = 1; i < amountOFchars; i++)
                {
                    strncpy(binaryNum, Base64Converter(decimalToBinary((int)ptr), 2));
                    fprintf(fixedfile,"0%d  %s\n" , ic ,binaryNum);
                    ptr++;
                    ic++;
                }
            }
            dhead= dhead->next;
        } /* END of symbol exist */

        if (symbolType == 'x') /* = extern */
        {

        }else if (symbolType == 'n') /* = entry */
        {
            ptr=skipsOnSpaces(line,ptr);
            ptr=skipsOnWORD(line,ptr);
            ptr=skipsOnSpaces(line,ptr);

            /* Pointing on .entry symbol */
            while(!isspace(ptr))
            {
                symbol[i] = ptr;
                ptr++;
                i++;
            }
             

            while (stemp != NULL)
            {
                if (!strcmp(stemp->symbolName,symbol))
                {
                    stemp.type->value = '1';
                    break;
                }
                stemp=stemp->next;
            }
            ic++;

            if (stemp.type->symbolName != '1')
            {
                errorsMassages(SYMBOL_NOT_EXIST);
            }
            stemp=shead;
        }else{ /* Its instruction line */
            isMinus = 0;
            memset(tmpArray, '0', 8);
            memcpy( tmpArray + 8,dhead->opcode,4);

            strncpy(binaryNum, Base64Converter(tmpArray));
            fprintf(fixedfile,"0%d  %s\n" , ic ,binaryNum);
            ic++;

            if (strcmp(dtail->ssymbol,"NULL"))
            {
                /* code */
            }

            if (!strcmp(dhead->ARE, "00") && !strcmp(dhead->sourceType,"000") || 
                  !strcmp(dhead->ARE, "00") && !strcmp(dhead->destinationType,"000") ){
                /* code */
            }

            if (*ptr == 45 ){
              isMinus = 1;
              ptr++;
            }
            else if (*ptr == 43 ){
                ptr++;
            }
            
            if (!isMinus){
                strcpy(binaryNum,Base64Converter( (decimalToBinary( positiveNumToNegative(atoi(ptr)) ,12 ))));
            }
            else{
                strcpy(binaryNum,Base64Converter( (decimalToBinary( atoi(ptr) ,12 ))));
            }
            fprintf(fixedfile,"0%d  %s\n" , ic ,binaryNum);
            ic++;

            if ( strcmp(dhead->sourceType,"000") && strcmp(dhead->opcode,"000") && 
                    strcmp(dhead->destinationType,"000") && strcmp(dhead->ARE,"00") )
            {
                /* return the location of the symbol from the symbol table*/
                i=0;
                while(!isspace(ptr))
                {
                    symbol[i] = ptr;
                    ptr++;
                    i++;
                }
                while (stemp != NULL)
                {
                    if (!strcmp(stemp->symbolName,symbol))
                    {
                        break;
                    }
                stemp=stemp->next;
                }

                strcpy(binaryNum,Base64Converter( (decimalToBinary(stemp->address,12 ))));
                fprintf(fixedfile,"0%d  %s\n" , ic ,binaryNum);

                /* Relocate address of symbol */
                initSource(line,ptr,dhead);
                initOpcode(line,ptr,dhead);
                initDestination(line,ptr,dhead);
                dhead->ARE="10";

                AddCodeATT(dtail->ssymbol,stail); /* need to delete */
                ic+=2;
                stemp=shead;
            } 

            dhead= dhead->next;
        }
        isMinus=0;
    }

    fclose(fixedfile);
    fclose(file);

    if (!isErrorFlag)
    {
        exit(0);
    }

}
