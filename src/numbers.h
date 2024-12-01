// numbers.h
#ifndef NUMBERS_H
#define NUMBERS_H

typedef struct {
    int* values;
    int count;
} NumberArray;

NumberArray read_numbers(char* line);
NumberArray read_numbers_from_file(const char* filename, int column);
NumberArray add_to_number_array(NumberArray numbers, int value);
void sort_numbers(NumberArray* arr);
void free_number_array(NumberArray* arr);

#endif
