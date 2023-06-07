#include <stdio.h>
#include <stdlib.h>
#include "errors.h"

void errorsMassages(const char* message) {
	fprintf(stderr, "Error! %s\n", message);
	exit(0);
}

try