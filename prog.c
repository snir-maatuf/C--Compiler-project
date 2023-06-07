#include "prog.h"
#include "errors.h"


int main(int argc, char *argv[]){

    proccesingFile(argc,*argv);
    return 0;

}


void proccesingFile(int argc, char *argv[]){
    int i;

    /* Checking file is recieved */
    if(argc >= 2){
        for(i = 1; i < argc; i++)
        {

            /* Builds a struct to one file */
            build_structs_File();

            /* Before first run (implement macros and write them to file)*/

            /* first run on code */

            /* second run on code */






        }
    }else
    {
        errorsMassages(MISSING_ARGUMENT);
    }
}

void build_structs_file(){

    

}


