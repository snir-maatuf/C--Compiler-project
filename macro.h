#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define MAX 100

struct Macro {
    char name[MAX];
    char data[MAX];
    struct Macro *next;
};

/* Macro functions */
void macroTable(struct Macro *head, char name[], char data[]);
void printMacro(struct Macro *tail);
int isMacro(char line[]);
int isEndMacro(char line[]);
void insertMacro(struct Macro *temp, char line[], FILE *fp);
int firstRead(int i, char *argv[], struct Macro *head);
int isCall(char line[], FILE *fpw, struct Macro *tail);
void preFile(int i, char *argv[], struct Macro *tail);

