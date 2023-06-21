#include "firstcheck.h"

/* chack the excactly type of instructions (Like: instruction start in point "." and more...) */

/* func that runs on each line the next code: */
/* isSymbol || enctern&extern || string&data */

/* call to dcode functions from dcode.h */
int isSymbol();
int stringORdata();





/* ליצור פונ שמדלגת על רווחים  ובנוסף בודקת את סוג הסמל המדויק( .extern\.sting.....)*/
void removeSpaces(char *str)
{
    int i;
    int count = 0;

    for (i = 0; str[i]; i++)
    {
        if (!isspace((char)str[i]))
            str[count++] = str[i];
    }

    str[count] = '\0';
}

/* This func goin though on the all lines in the file */
int firstCheck(int x){
    int DC = 0, IC = 100, flag = 1;
    char fileName[MAX];
    int * p = NULL;
    FILE * file;
    char symbolType, *token;
    char line[MAX] = {'\0'};
    struct  symolTable* shead= NULL;
    struct  Decode* dhead= NULL;



    /* Create new decode linkedlist and symbol table */
    dhead = (struct Decode*)malloc(sizeof(struct Decode));
    shead = (struct Stable*)malloc(sizeof(struct symbolTable));

    file = fopen(fileName, 'r');
    if (file == NULL)
    {
        printf("Error! Can't opening file: %s\n", file);
    }

    /* initialize fileName by strcpy func */
    /* missing here the get the file name and insert to fileName */
    strncat(fileName, ".am", 3);

    token = strtok(line," ");



    /* Read each line and */
    while (fgets(line, MAX, p)){
        /* Create a new node of the decode linkedlist and also symbolTable linkedlist node */
        struct  Decode* dtemp= NULL;
        struct  Stable* stemp = NULL;
        dtemp = (struct Decode*)malloc(sizeof(struct Decode));
        stemp = (struct Stable*)malloc(sizeof(struct symbolTable));


        /* ignore from spaces */

        /* Skip on comment line and empty line */
        if( *line == ';' || isspace(*line) ){
            p++;
            continue;
        }

        /* define the completely command name  */
        symbolType = getSymbolChr(token);

        switch (symbolType)
        {
            case 'a':/* =data */
                /* check if its data or string */
                /* code */
                break;

            case 't': /* =string */
                /* code */
                break;
            case 'o': /* = code */
                /* code */
                break;
            case 'n': /* =entry*/
                /* code */
                break;
            case 'x': /* =extern*/
                /* code */
                break;

            default:
                break;
        }

        /* ... (All the function on each line ) */
    }
    fclose(file);

    return flag;
}
