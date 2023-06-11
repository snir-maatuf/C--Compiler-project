#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

struct symbolTable {
    char symbolName [MAX]; 
    int value;
    int address;
    int offset;
    char attributes[5];
    struct symbolTable* next;
};

/* Add symbol data to the "Symbol Table" */
void addSimbolToTable(struct symbolTable * head, char symbol[], int data);
/*  */
void addattributes(struct Stable *tail , int type, char symbol[]);
/* Return which type commmand is the attribute */
int attributetype(char type[]);