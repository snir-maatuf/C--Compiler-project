#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

struct symbolTable {
    char symbolName [MAX]; 
    int value; // need to delete
    int address;
    struct InstructsType type; //need to delete
    struct symbolTable* next;
};

struct InstructsType {
    const char *symbolName;
    int value;
};

struct InstructsType types[] = {
        {".data", 0},
        {".string", 0},
        {".entry", 1},
        {".extern", 2}
    };




void addSymbolToTable(struct symbolTable * head, char symbol[], int data);
void addInstructionToTable( char symbol[] ,int type, struct symbolTable * head );
int getSymbolType(char type[]);
char getSymbolChr(char* type);
void printEntFile(int i, char * argv[], struct symbolTable *tail);
void printExtFile(int i, char * argv[], struct symbolTable *head);
int getSymbolType(char type[]);
int freeSymbol(struct symbolTable *symbol);
