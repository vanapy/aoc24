#include <stdio.h>
#include <stdlib.h>
#include "input.h"

NumberArrays read_two_columns_from_file(const char* filename) {
    NumberArrays result = {{0}, {0}}; // Initialize both arrays

    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Unable to open file");
        return result; // returning empty struct on failure
    }

    int value1, value2;
    while (fscanf(file, "%d %d", &value1, &value2) == 2) {
        result.numbers1 = add_to_number_array(result.numbers1, value1);
        result.numbers2 = add_to_number_array(result.numbers2, value2);
    }

    fclose(file);

    // Assuming both arrays should have the same count
    result.numbers1.count = result.numbers2.count;
    return result;
}
