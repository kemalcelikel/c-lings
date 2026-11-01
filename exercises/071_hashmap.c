//
// Implementing a simple Hash Map in C usually involves:
// 1. A hash function to map keys to indices.
// 2. Handling collisions (we'll ignore collisions for this simple example).
// This deliberately limited table overwrites colliding entries. It is not a
// complete map: keys are at most 19 characters, and values must be nonnegative
// because -1 means not found. The sample keys below have distinct hash values.
//

#include <stdio.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct {
    char key[20];
    int value;
} Entry;

Entry hash_table[TABLE_SIZE];

// A very simple hash function
unsigned int hash(const char *key) {
    unsigned int sum = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        sum += (unsigned char)key[i];
    }
    return sum % TABLE_SIZE;
}

int put(const char *key, int value) {
    if (strlen(key) >= sizeof(hash_table[0].key) || value < 0) return 0;
    unsigned int idx = hash(key);
    // (Problem 1)
    // Copy the key into the table at index 'idx'.
    // strcpy(dest, src)
    strcpy(???, key);
    hash_table[idx].value = value;
    return 1;
}

int get(const char *key) {
    unsigned int idx = hash(key);
    // (Problem 2)
    // Check if the key at 'idx' matches the requested key.
    // strcmp returns 0 if strings are equal.
    if (strcmp(hash_table[idx].key, key) == ???) {
        return hash_table[idx].value;
    }
    return -1; // Not found
}

int main(void) {
    if (!put("apple", 100) || !put("banana", 200)) return 1;

    printf("apple: %d\n", get("apple"));
    printf("banana: %d\n", get("banana"));
    
    // Collision warning! 'orange' might collide with others in a real app.
    // This is a naive implementation.
    
    return 0;
}

// CHECK: apple: 100
// CHECK: banana: 200
