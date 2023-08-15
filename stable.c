#include "stable.h"

#define MAX_LABLE 31


/* Add symbol data to node in the "Symbol Table" */
void addSymbolToTable(struct symbolTable * head, char symbol[], int data){
    struct symbolTable *newSymbol = NULL;
    struct symbolTable *tmp = NULL;
    


    /* Check if the symbol is already exists */
    for (tmp = head; tmp!= NULL; tmp = tmp->next){
        if (!(strcmp(tmp->symbolName, symbol))) {
            exit(0);
        }
    }
    
    newSymbol = (struct symbolTable*)malloc(sizeof(struct symbolTable));
    if(!head){
        errorsMassages(MEMORY_ALLOCAION_FAILED);
        exit(0);
    }

    strcpy(newSymbol->symbolName,symbol);
    strcpy(tmp->type.symbolName,"none");
    newSymbol->address = data - data %16;
    head->next = tmp;

    /* tmp pointing to the last node that initialize (we did it up) */
    tmp->next = newSymbol;
    newSymbol->next = NULL;
}



/*  Add symbols to the table */
void addInstructionToTable( char symbol[] , struct symbolTable * head ){
    struct symbolTable *newSymbol = NULL;
    struct symbolTable * tmp = head;

    newSymbol = (struct symbolTable*)malloc(sizeof(struct symbolTable));
    if (!newSymbol) {
        errorsMassages(MEMORY_ALLOCAION_FAILED);
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
        if (strcmp(tmp->type.symbolName, ".entry" ) == 0 )
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
        if (strcmp(tmp->type.symbolName, ".extern" ) == 0 )
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
    int i;
    numTypes = sizeof(types) / sizeof(types[0]);

    /* Checking with each type which type is using */
    for (i = 0; i < numTypes; i++) {
        if ( !strcmp(type, types[i].symbolName) ) {
            return types[i].value;
        }
    } 

    return -1;
}


/* Return the corresponding CHR of the instruction type */
char getSymbolChr(char* type) {
    int i;
    for (i = 0; i <= 3; i++) {
        if (strcmp(type, types[i].symbolName) == 0) {
            return types[i].symbolName[2];
        }
    }
    return '\0'; /* The command not found */
}

/* Check if the given symbol is already in the symbol table */
int isSymbolExist(char* ptr){
    char * labelName[];
    struct symbolTable SymbolTableNode;
    int wordLength = 0;
    

    while (*ptr && isalpha(*ptr)) {
        wordLength++;
    }

    for (int i = 0; i < wordLength && i < MAX_LABLE; i++) {
        labelName[i] = ptr;
        ptr++;
    }
    
    while (SymbolTableNode->symbolName != NULL) {
        if (strncmp(SymbolTableNode->symbolName, labelName, wordLength)) {
            return 0;
        }
        SymbolTableNode = SymbolTableNode->next;
    }

    free(curr)
    return 1; /* Symbol is not exists */
}


/* Free the "symbol table" from the memory */
int freeSymbol(struct symbolTable *symbol) {
    free(symbol->symbolName);
    free_list(symbol->type, free);
    free_list(symbol->next, free);
    free(symbol);
    return 0;
}
