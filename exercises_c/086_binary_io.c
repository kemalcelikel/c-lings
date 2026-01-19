//
// For binary data, we use fread and fwrite.
// They read/write raw bytes, not text.
//
//     fwrite(ptr, size, count, stream)
//     fread(ptr, size, count, stream)
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
    if (f) {
        // (Problem 1)
        // Write the struct to the file.
        // Ptr, Size of Element, Count, Stream
        fwrite(&r1, sizeof(Record), 1, f);
        fclose(f);
    }

    // Read
    Record r2;
    f = fopen("data.bin", "rb");
    if (f) {
        // (Problem 2)
        // Read back into r2.
        fread(&r2, sizeof(Record), 1, f);
        fclose(f);
        
        printf("Read: ID=%d, Val=%.2f\n", r2.id, r2.value);
    }

    return 0;
}

// CHECK: Read: ID=1, Val=3.14

