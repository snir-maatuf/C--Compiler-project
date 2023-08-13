#include <ctype.h>
#include "errors.h"
#include "stable.h"
#include "dcode.h"

const char *instructionsNames[] = {"mov", "cmp", "add","sub", "not", "clr","lea", "inc", "dec","jmp", "bne", "red","prn", "jsr", "rts", "stop"};


char * skipsOnWORD(char line[],char * ptr);
char * skipsOnSpaces(char line[],char * ptr);
void zeroOperands(char * line,char * ptr,struct Dcode * dtemp);
void codingOneOprand(char line[], char * ptr, struct Dcode * dcurr);
void codingTwoOprands(char line[], char * ptr, struct Dcode * dcurr);
void initOpcode(char line[], char * ptr, struct Dcode * dcurr);
void initSource(char line[], char * ptr, struct Dcode * dcurr);
void initDestination(char line[], char * ptr, struct Dcode * dcurr);
int isImmediate(char line[], char * ptr, struct Dcode * dcurr);
int isDirective(char line[], char * ptr, struct Dcode * dcurr);
int isRegister(char line[], char * ptr, struct Dcode * dcurr);
char * getRegisterBinaryNumber(char line[], char * ptr, struct Dcode * dcurr){
void initOperand(char addressNumber[],char * ptr, struct Dcode * dcurr, int isTwoRegisters );
char * operandsType(char line[], char * token, struct Dcode * dcurr);
char* decimalToBinary(int decimalNum, int limitNumberOFbits);
int isInstructionName(char * ptr);
char * skipToInstructType( char line[], char * ptr);
int isSymbol(char line[], char * ptr, struct symbolTable * shead);
int dcString(char line[] , char * ptr, struct Dcode * dcurr);
int dcCounter(char line[],char * ptr, struct Dcode * dcurr);
void insert10Bits(struct Dcode * dcurr ,char * binaryString, int isMinus);
int positiveNumToNegative(int num);
void removeSpacesAndTabs(char *line);
int firstCheck(int fileIndex, char *argv[], struct symbolTable shead, struct Decode dhead, int ic, int dc);
