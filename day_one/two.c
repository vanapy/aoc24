#include <stdio.h>
#include <stdlib.h>
#include "../src/numbers.h"
#include "input.h"

#define TABLE_SIZE 1000 // Define table size (you can adjust this)

// move has table functions to common part
// Struct for each entry in the hash table
typedef struct Entry {
    int key;
    int count;
    struct Entry* next; // For handling collisions using chaining
} Entry;

// Hash table definition
typedef struct HashTable {
    Entry** table; // Array of pointers to Entries
} HashTable;

// Function to create a hash table
HashTable* createHashTable() {
    HashTable* ht = malloc(sizeof(HashTable));
    ht->table = malloc(sizeof(Entry*) * TABLE_SIZE);
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
    return ht;
}

// Simple hash function
int hash(int key) {
    return key % TABLE_SIZE;
}

// Function to insert/update the count of an integer in the hash table
void insert(HashTable* ht, int key) {
    int index = hash(key);
    Entry* current = ht->table[index];

    while (current != NULL) {
        if (current->key == key) {
            current->count++;
            return; // Key found, increment count and exit
        }
        current = current->next;
    }

    // Key not found, create a new entry
    Entry* newEntry = malloc(sizeof(Entry));
    newEntry->key = key;
    newEntry->count = 1;
    newEntry->next = ht->table[index];
    ht->table[index] = newEntry; // Insert new entry
}

// Function to print the counts
void printCounts(HashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Entry* current = ht->table[i];
        while (current != NULL) {
            printf("Value: %d Count: %d\n", current->key, current->count);
            current = current->next;
        }
    }
}

// Function to free the hash table
void freeHashTable(HashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Entry* current = ht->table[i];
        while (current != NULL) {
            Entry* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(ht->table);
    free(ht);
}

// Function to get the count of a specific key
int getCount(HashTable* ht, int key) {
    int index = hash(key);
    Entry* current = ht->table[index];

    while (current != NULL) {
        if (current->key == key) {
            return current->count; // Key found, return count
        }
        current = current->next;
    }

    return 0; // Key not found, return 0
}

int main() {
    int result = 0;
    NumberArrays arrays = read_two_columns_from_file("inputs/day_one.txt");
    HashTable* ht = createHashTable();

    // Insert each number into the hash table
    for (int i = 0; i < arrays.numbers2.count; i++) {
        insert(ht, arrays.numbers2.values[i]);
    }

    for (int i = 0; i < arrays.numbers1.count; i++) {
        int count = getCount(ht, arrays.numbers1.values[i]);
        // printf("Value: %d Count: %d\n", valuesToCheck[i], count);
        result += arrays.numbers1.values[i] * count;
    }

    // Free the hash table
    freeHashTable(ht);
    printf("%d ", result);
    return 0;
}
