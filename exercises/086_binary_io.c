//
// For binary data, we use fread and fwrite.
// They read/write raw bytes, not text.
//
//     fwrite(ptr, size, count, stream)
//     fread(ptr, size, count, stream)
// These return the number of complete elements transferred. Check the return
// value before using read data. Raw struct files depend on padding, byte order,
// and type representations; this is a same-program round trip, not a portable
// serialization format. Do not use this format for exchanging untrusted data.
//

#include <stdio.h>

typedef struct {
    int id;
    float value;
} Record;

int main(void) {
    Record r1 = { 1, 3.14f };
    
    // Write
    FILE *f = fopen("data.bin", "wb");
    if (f == NULL) return 1;
    // (Problem 1)
    // Write the struct to the file.
    // Ptr, Size of Element, Count, Stream
    int wrote = fwrite(???, sizeof(Record), 1, f) == 1;
    int closed = fclose(f) == 0;
    if (!wrote || !closed) return 1;

    // Read
    Record r2;
    f = fopen("data.bin", "rb");
    if (f == NULL) return 1;
    // (Problem 2)
    // Read back into r2.
    int read_ok = fread(???, sizeof(Record), 1, f) == 1;
    closed = fclose(f) == 0;
    if (!read_ok || !closed) return 1;
        
    printf("Read: ID=%d, Val=%.2f\n", r2.id, r2.value);

    return 0;
}

// CHECK: Read: ID=1, Val=3.14
