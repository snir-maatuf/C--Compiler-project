#include "firstcheck.h"

/* chack the excactly type of instructions (Like: instruction start in point "." and more...) */

/* func that runs on each line the next code: */
/* isSymbol || enctern&extern || string&data */

/* call to dcode functions from dcode.h */
int isSymbol();
int stringORdata();

/* ליצור פונ שמדלגת על רווחים  ובנוסף בודקת את סוג הסמל המדויק( .extern\.sting.....)*/

/* This func goin though on the all lines in the file */
int firstCheck(int x){
    int DC = 0;
    int IC = 100;
    int flag = 1;
    int line[MAX];
    int fileName[MAX];
    int * p = NULL;
    FILE * file;
    char symbolType;

    file = fopen(fileName, 'r');

    /* Create new symbol table */

    /* Create new decode linkedlist */

    /* Read each line and */
    while (fgets(line, MAX, p)){
        /* Create a new node of the decode linkedlist and also the Stable linkedlist */
        /* ignore from spaces */
        
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
    fclose();

    return flag; 
}

להתעלםMAIN: mov r , e
