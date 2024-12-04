#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// Function to extract numbers from mul(a,b) pattern and multiply them
long long extract_and_multiply(const char *str) {
    const char *p = str + 4;  // Skip "mul("
    char num1[256] = {0};
    char num2[256] = {0};
    int i = 0;

    // Extract first number
    while (isdigit(*p)) {
        num1[i++] = *p++;
    }
    num1[i] = '\0';

    // Skip comma and spaces
    while (*p && (*p == ',' || *p == ' ')) p++;

    // Extract second number
    i = 0;
    while (isdigit(*p)) {
        num2[i++] = *p++;
    }
    num2[i] = '\0';

    return (long long)atoll(num1) * atoll(num2);
}

int is_valid_mul_format(const char *str) {
    const char *p = str;

    // Check for "mul(" prefix
    if (strncmp(p, "mul(", 4) != 0) return 0;
    p += 4;

    // Check first number
    if (!isdigit(*p)) return 0;
    while (isdigit(*p)) p++;

    // Check comma
    if (*p != ',') return 0;
    p++;

    // Skip whitespace after comma
    while (*p == ' ') p++;

    // Check second number
    if (!isdigit(*p)) return 0;
    while (isdigit(*p)) p++;

    // Check closing parenthesis
    if (*p != ')' || *(p + 1) != '\0') return 0;

    return 1;
}

void find_mul_patterns(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error\n");
        return;
    }

    int result = 0;
    char buffer[1024] = {0};
    int pos = 0;
    int c;

    while ((c = fgetc(file)) != EOF) {
        if (c == 'm') {
            memset(buffer, 0, sizeof(buffer));
            pos = 0;
            buffer[pos++] = c;
        }
        else if (pos > 0) {
            buffer[pos++] = c;

            if (c == ')') {
                buffer[pos] = '\0';
                if (is_valid_mul_format(buffer)) {
                    // printf("%s\n", buffer);
                    result += extract_and_multiply(buffer);
                }
                pos = 0;
                memset(buffer, 0, sizeof(buffer));
            }

            if (pos >= sizeof(buffer) - 1) {
                pos = 0;  // Reset if buffer is full
                memset(buffer, 0, sizeof(buffer));
            }
        }
    }
    printf("%d", result);
    fclose(file);
}

int main() {
    find_mul_patterns("inputs/day_three.txt");
    return 0;
}
