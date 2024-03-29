#include "prog.h"
#include "errors.h"

/* consider to make ic dc to global variables */

int main(int argc, char *argv[]){

    proccesingFile(argc,*argv);
    return 0;

}


void proccesingFile(int argc, char *argv[]){
    int fileIndex;
    int ic =100, dc =0, flag;

    /* Checking file is recieved */
    if(argc >= 2){
        for(fileIndex = 1; fileIndex < argc; fileIndex++)
        {
            /* Builds a structs */
            struct symbolTable* shead = NULL;
            struct Decode* dhead = NULL;
            struct Macro* Mhead = NULL;

            shead = (struct symbolTable*)malloc(sizeof(symbolTable));
            dhead = (struct Decode*)malloc(sizeof(struct Decode));
            Mhead = (struct Macro*)malloc(sizeof(struct Macro));

            /* Before first run (implement macros read and write the macro)*/
            flag = preFile(fileIndex, argv, Mhead);

            /* first run on code */
            if (flag == 0)
            {
                /* execute here macro func (write them to file)*/
                flag = firstcheck(fileIndex, argv,shead,dhead, &ic, &dc);
            }

            /* second run on code */
            if (flag == 0)
            {
                secondcheck(fileIndex,shead, dhead, argv, &ic, &dc);
            }
            printEntFile(filename,argv,dhead);
            printExtFile(filename,argv,dhead);
        }
    }else
    {
        errorsMassages(MISSING_ARGUMENT);
    }
}
