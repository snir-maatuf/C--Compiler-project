#include "stable.h"


void addSimbolToTable(struct symbolTable * head, char symbol[], int data){
    struct symbolTable *temp = NULL;

    temp = (struct symbolTable*)malloc(sizeof(struct symbolTable));
    strcpy(temp->symbolName,symbol);
    temp ->value = data;
    strcpy(temp->attributes,"0000");
    temp ->address = data - data %16;
    temp ->offset = data % 16 ;
    head ->next = temp;
}


void addattributes(struct Stable *tail , int type, char symbol[]){
    struct  Stable *temp = NULL;

}


int attributetype(char type[]) {
    int numTypes;
    AttributeType types[] = {
        {".data", 0},
        {".string", 0},
        {".code", 1},
        {".entry", 2},
        {".extern", 3}
    };

    numTypes = sizeof(types) / sizeof(types[0]);

    /* Checking with each type which type is using */
    for (int i = 0; i < numTypes; i++) {
        if ( !strcmp(type, types[i].symbolName) ) {
            return types[i].value;
        }
    }

    return -1;
}


void printEntriesFile(int i, char *args[], struct symboleTable *tail){
    FILE * fp;
    char fname[MAX];
    struct symbolTable *temp = NULL;

    /* ------------------------ MISSING ---------------*/
    /* */
    /* */


    fp = fopen(fname, "w");
    if (fp == NULL) {
        printf("Failed to open file: %s\n", fname);/* ---------------------CHANGE ---------------*/
        return;
    }
    
    temp = (struct symbolTable *)malloc(sizeof(struct simboleTable));


}


