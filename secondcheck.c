#include "secondcheck.h"

#define MAX_LINE 80

/* This func goin though on the all lines in the file */
int secondCheck(int fileIndex, char *argv[], struct symbolTable shead, struct Decode dhead, int ic, int dc){
    char fileName[MAX_LINE];
    int number[MAX_LINE];
    char binaryNumber[9];
    FILE * file;
    FILE * fixedfile;
    char * ptr;
    char line[MAX_LINE] = {'\0'};
    char fname[MAX_LINE];
    char fname2[MAX_LINE];
    int lineLength,i,amountOFnumbers, isErrorFlag = 0, isMinus=0;
    char symbolType;
    ic =0;




    strcpy(fname, argv[fileIndex]);
    strcpy(fname2, argv[fileIndex]);
    strncat(fname2, ".am", 3);

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

    

    while (fgets(line, MAX_LINE, file)){
        ptr=skipsOnSpaces(line,ptr);
        

        if (isSymbolExist(ptr) )
        {
            ptr=skipsOnWORD(line,ptr);   main: .data    +6, 7
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
                            strncpy(binaryNumber,decimalToBinary( positiveNumToNegative(atoi(ptr)) ,10 ),10);
                        }
                        else
                        {
                            strncpy(binaryNumber,decimalToBinary( atoi(ptr) ,10 ),10);

                        }
                        
                        
                        

                    }
                }
                
                

            }else if (symbolType == 't') /* = string */
            {
                /* code */
            }
            
            

            if (symbolType == 'n') /* = extern */
            {

        }

            
        }




    }
    if (!isErrorFlag)
    {
        exit(0);
    }
    




}


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





