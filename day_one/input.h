#include <stdio.h>
#include <stdlib.h>
#include "../src/numbers.h"

typedef struct {
    NumberArray numbers1;
    NumberArray numbers2;
} NumberArrays;

NumberArrays read_two_columns_from_file(const char* filename);
