#include "errors.h"
#include "stable.h"
#include "dcode.h"
#include <ctype.h>


#define MAX 100

int isSymbolExist(struct symbolTable head,const char* ptr);
int isSymbol();
char *skipSpacesAndTabs(char *str);
void removeSpacesAndTabs(char *line);
int firstCheck(int fileIndex, char *argv[], struct symbolTable *shead, struct Decode *dhead);
