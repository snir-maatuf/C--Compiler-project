#include "prog.h"
#include "errors.h"


int main(int argc, char *argv[]){

    proccesingFile(argc,*argv);
    return 0;

}


void proccesingFile(int argc, char *argv[]){
    int file_index;
    int ic,dc;

    /* Checking file is recieved */
    if(argc >= 2){
        for(file_index = 1; file_index < argc; file_index++)
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


