#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


struct Decode {
    int ic;
    char sourceType[3];
    char opcode[4];
    char destinationType[3];
    char ARE[2];
    int binaryNumber[10];
    struct Decode* next;
}

char* opcodeToBinary(char *ptr);
int instructionGroup(char line[], char * p);
Dcode * appendNode(struct Dcode * dcurr );
