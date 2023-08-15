#include "errors.h"


char BASE64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


int numbersCounter(char line[], char * ptr);
int charsCounter(char line[], char * ptr);
char Base64Converter(char *binaryNum);
int secondCheck(int fileIndex, char *argv[], struct symbolTable *shead, struct Decode *dhead, int ic, int dc);
