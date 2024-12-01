#include <stdio.h>
#include <stdlib.h>
#include "../src/numbers.h"
#include "input.h"

// remove repetitions
int main() {
    int result = 0;
    NumberArrays arrays = read_two_columns_from_file("inputs/day_one.txt");
    sort_numbers(&arrays.numbers1);
    sort_numbers(&arrays.numbers2);
    for (int i = 0; i < arrays.numbers1.count; i++) {
       int diff = abs(arrays.numbers1.values[i] - arrays.numbers2.values[i]);
       result += diff;
    }
    printf("\n");
    free_number_array(&arrays.numbers1);
    free_number_array(&arrays.numbers2);
    printf("%d ", result);
    return result;
}
