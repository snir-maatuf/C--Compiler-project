#include "stable.h"


/* Add symbol data to the "Symbol Table" */
void addSymbolToTable(struct symbolTable * head, char symbol[], int data){
    struct symbolTable *newSymbol = NULL;
    struct symbolTable *tmp = NULL;


    /* Check if the symbol is already exists */
    for (tmp = head; tmp!= NULL; tmp = tmp->next){
        if (!(strcmp(tmp->symbolName, symbol))) {
            exit(0); /*-------------------- SET ERROR CONST ----------------------- */
        }
    }
    
    newSymbol = (struct symbolTable*)malloc(sizeof(struct symbolTable));

    if(!head){
        exit(0);  /*-------------------- SET ERROR CONST ----------------------- */
    }

    strcpy(newSymbol->symbolName,symbol);
    strcpy(tmp->instructionType,"0000");
    newSymbol->value = data;
    newSymbol->address = data - data %16;
    tmp->offset = data % 16 ;
    head->next = tmp;

    /* tmp pointing to the last node that initialize (we did it up) */
    tmp->next = newSymbol;
    newSymbol->next = NULL;
}



/*  Add symbols to the table */
void addInstructionToTable( char symbol[] ,int type, struct symbolTable * head ){
    struct symbolTable *newSymbol = NULL;
    struct symbolTable * tmp = head;

    newSymbol = (struct symbolTable*)malloc(sizeof(struct symbolTable));
    if (!newSymbol) {
        fprintf(stderr, "Memory allocation failed.\n"); /*-------------------- SET ERROR CONST ----------------------- */
        exit(0);
    }
    

    if ( !(head) ) {
        /*  The linked list is empty, so set the new symbol as the head */
        head = newSymbol;
    } else {
        /* Traveling on the linkedlist and append the newSymbol at the end node */
        while (tmp->next != NULL) {
            if(!strcmp(tmp ->symbolName,symbol)){
                tmp = tmp->next;
                return;
            }
        }
        tmp->next = newSymbol;
        newSymbol->next=NULL;
    }
}


/* Return instruction of the current symbol node */
const char* printInstructionType(struct symbolTable* tmp) {
    static char new[MAX];

    memset(new, '\0', MAX);

    if (tmp->instructionType[0] > '0')
        strcat(new, "data ");
    if (tmp->instructionType[1] > '0')
        strcat(new, "code ");
    if (tmp->instructionType[2] > '0')
        strcat(new, "entry ");
    if (tmp->instructionType[3] > '0')
        strcat(new, "extern ");
    return new;
}


/* Prints the entries to a file */
void printEntFile(int i, char * argv[], struct symbolTable *head){
    FILE * fp;
    char fileName[MAX];
    struct symbolTable * tmp = NULL;
    char file_type[] = ".ent.txt";
    
    /* Store file name with the expected name */
    strcpy(fileName, argv[i]);
    strcat(fileName, file_type);

    fp = fopen(fileName, "w");
    if (fp == NULL) {
        printf("Failed to open file: %s\n", fileName);/* ---------------------CHANGE ---------------*/
        return;
    }
    
    tmp = head->next;

    /* Print each instruction and his location in the memory */
    while( !tmp )
    {
        if (tmp->instructionType[2] > '0')
        {
            fprintf(fp," %s\t%d\n",tmp->symbolName,tmp->address);
        }
        tmp = tmp-> next;
    }

    fclose(fp);
}


/* Prints the externals to a file */
void printExtFile(int i, char * argv[], struct symbolTable *head){
    FILE * fp;
    char fileName[MAX];
    struct symbolTable * tmp = NULL;
    char file_type[] = ".ext.txt";
    
    /* Store file name with the expected name */
    strcpy(fileName, argv[i]);
    strcat(fileName, file_type);

    fp = fopen(fileName, "w");
    if (fp == NULL) {
        printf("Failed to open file: %s\n", fileName);/* ---------------------CHANGE ---------------*/
        return;
    }
    
    tmp = head->next;

    /* Print each instruction and his location in the memory */
    while( !tmp )
    {
        if (tmp->instructionType[3] > '0')
        {
            fprintf(fp," %s\t%d\n", tmp->symbolName , tmp->address );
        }
        tmp = tmp-> next;
    }

    fclose(fp);
}


/* Return the corresponding value of the instruction type */
int getSymbolType(char type[]) {
    int numTypes;
    numTypes = sizeof(types) / sizeof(types[0]);

    /* Checking with each type which type is using */
    for (int i = 0; i < numTypes; i++) {
        if ( !strcmp(type, types[i].symbolName) ) {
            return types[i].value;
        }
    }

    return -1;
}


char getSymbolChr(char* type) {
    int i;
    for (i = 0; i <= 4; i++) {
        if (strcmp(type, types[i].symbolName) == 0) {
            return types[i].symbolType[2];
        }
    }
    return '\0'; /* The command not found */
}




/* Free the "symbol table" from the memory */
int freeSymbol(struct symbolTable *symbol) {
    free(symbol->symbolName);
    free_list(symbol->instructionType, free);
    free_list(symbol->next, free);
    free(symbol);
    return 0;
}
