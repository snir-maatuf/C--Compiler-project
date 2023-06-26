#include "firstcheck.h"

struct Decode { /* לא עברתי על זה*/
    char symbol[MAX];
    char opcode [21];
    char funct [5];
    char sregister [5];
    char saddress[3];
    char dregister [5];
    char daddress [3];
    char ssymbol [MAX];
    char dsymbol [MAX];
    char dataorstring[MAX];
    struct Decode* next;
};