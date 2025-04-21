#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *self, *copy;
    char c;
    
    // Open the source file (this program itself)
    self = fopen(argv[0], "rb");
    if (self == NULL) {
        perror("Error opening source file");
        return 1;
    }
    
    // Create a copy with a different name
    copy = fopen("copy_of_program.exe", "wb");
    if (copy == NULL) {
        perror("Error creating copy");
        fclose(self);
        return 1;
    }
    
    // Copy the content byte by byte
    while ((c = fgetc(self)) != EOF) {
        fputc(c, copy);
    }
    
    // Close files
    fclose(self);
    fclose(copy);
    
    printf("Created a copy of this program as 'copy_of_program.exe'\n");
    
    return 0;
}