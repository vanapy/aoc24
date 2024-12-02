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
       int is_good = 1;
       int prev;
       int sign = 0;
       int* numbers = parse_line(line, &count);

       // Print or process numbers
       for (int i = 0; i < count; i++) {
           if (i > 0) {
               if (((get_sign(numbers[i] - prev) != sign) || (get_abs_difference(numbers[i], prev)) > 3)) {
                  is_good = 0;
                  break;
               }
           }
           sign = get_sign(numbers[i] - prev);
           prev = numbers[i];
       }
       // printf("%d", good_lines_count);
       good_lines_count += is_good;
       free(numbers);
   }
   printf("%d ", good_lines_count);
   fclose(file);
   return 0;
}
