#include "prog.h"
#include "errors.h"

/* consider to make ic dc to global variables */

int main(int argc, char *argv[]){

    proccesingFile(argc,*argv);
    return 0;

}


void proccesingFile(int argc, char *argv[]){
    int file_index;
    int ic, dc, flag;

    /* Checking file is recieved */
    if(argc >= 2){
        for(file_index = 1; file_index < argc; file_index++)
        {
            /* Builds a struct to one file */
            buildStructsFile();

            /* Before first run (implement macros read them)*/
            flag = /* execute macro function */ ;

            /* first run on code */
            if (!flag)
            {
                /* execute here macro func (write them to file)*/
                flag = firstcheck(file_index, argv);
            }

            /* second run on code */
            if (!flag)
            {
                secondcheck();
            }


        }
    }else
    {
        errorsMassages(MISSING_ARGUMENT);
    }
}


void buildStructsFile(){
    struct  symbolTable* table = NULL;
    struct  Decode* dhead = NULL;

    table = (symbolTable*)malloc(sizeof(symbolTable));
    dhead = (struct Decode*)malloc(sizeof(struct Decode));

}

