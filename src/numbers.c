// numbers.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "numbers.h"

NumberArray read_numbers(char* line) {
    NumberArray result = {NULL, 0};
    int capacity = 10;
    result.values = malloc(capacity * sizeof(int));

    char* token = strtok(line, " \n");
    while (token != NULL) {
        if (result.count >= capacity) {
            capacity *= 2;
            result.values = realloc(result.values, capacity * sizeof(int));
        }
        sscanf(token, "%d", &result.values[result.count++]);
        token = strtok(NULL, " \n");
    }

    return result;
}

void free_number_array(NumberArray* arr) {
    free(arr->values);
    arr->values = NULL;
    arr->count = 0;
}

// replace woth qsort later
void sort_numbers(NumberArray* arr) {
    for (int i = 0; i < arr->count - 1; i++) {
        for (int j = 0; j < arr->count - i - 1; j++) {
            if (arr->values[j] > arr->values[j + 1]) {
                int temp = arr->values[j];
                arr->values[j] = arr->values[j + 1];
                arr->values[j + 1] = temp;
            }
        }
    }
}

#define INITIAL_CAPACITY 4

NumberArray add_to_number_array(NumberArray numbers, int value) {
    // Check if count equals capacity (since capacity is not explicitly defined, we'll need to manage it)
    if (numbers.count % INITIAL_CAPACITY == 0) {
        // If it's the first element, allocate the initial capacity
        size_t new_capacity = (numbers.count == 0) ? INITIAL_CAPACITY : numbers.count * 2;
        int* new_values = realloc(numbers.values, new_capacity * sizeof(int));
        if (!new_values) {
            perror("Unable to allocate memory");
            return numbers; // Return the original NumberArray if realloc fails
        }
        numbers.values = new_values; // Update the values pointer
    }

    // Add the new value to the array
    numbers.values[numbers.count] = value;
    numbers.count++; // Increment the count

    return numbers; // Return the updated NumberArray
}
