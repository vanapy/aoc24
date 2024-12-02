#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int* parse_line(char* line, int* count) {
   *count = 0;
   int capacity = 10;
   int* numbers = malloc(capacity * sizeof(int));

   char* token = strtok(line, " ");
   while (token != NULL) {
       if (*count >= capacity) {
           capacity *= 2;
           numbers = realloc(numbers, capacity * sizeof(int));
       }
       numbers[(*count)++] = atoi(token);
       token = strtok(NULL, " ");
   }
   return numbers;
}

int get_sign(int x) {
   return (x > 0) ? 1 : ((x < 0) ? -1 : 0);
}

int get_abs_difference(int x, int y) {
    return abs(x - y);
}

int main() {
    int good_lines_count = 0;
    FILE* file = fopen("inputs/day_two.txt", "r");
    char line[1024];

   while (fgets(line, sizeof(line), file)) {
       int count;
       int good_counter = 0;
       int prev;
       int* numbers = parse_line(line, &count);
       int sign = get_sign(numbers[1] - numbers[0]);;

       for  (int e = 0; e < count; e++) {

           int is_good = 1;
           if (e == 0) {
               sign = get_sign(numbers[2] - numbers[1]);
           } else if (e == 1) {
                sign = get_sign(numbers[2] - numbers[0]);
           } else {
               sign = get_sign(numbers[1] - numbers[0]);
           }
           for (int i = 0; i < count; i++) {
               if (i != e) {
                   // printf("%d ", numbers[i]);
                   if (((i > 0) & (e > 0)) || ((i > 1) & (e == 0))) {
                       if (((get_sign(numbers[i] - prev) != sign) || (get_abs_difference(numbers[i], prev)) > 3)) {
                           is_good = 0;
                           break;
                       }
                   }
                   prev = numbers[i];
               }
           }
           good_counter += is_good;
       }
       // printf("%d \n", good_counter);
       if (good_counter > 0) {
           good_lines_count += 1;
       }
       free(numbers);
   }
   printf("%d ", good_lines_count);
   fclose(file);
   return 0;
}
