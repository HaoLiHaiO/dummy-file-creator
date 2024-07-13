#include <stdio.h>
#include <stdlib.h>

#define FILE_SIZE (10 * 1024 * 1024) // 10MB

int main() {
    FILE *file = fopen("dummyfile.bin", "wb");
    if (!file) {
        perror("Failed to create file");
        return EXIT_FAILURE;
    }

    char buffer[1024] = {0}; // 1KB buffer init to 0

    for (int i = 0; i < FILE_SIZE / sizeof(buffer); i++) {
        if (fwrite(buffer, sizeof(buffer), 1, file) != 1) {
            perror("Failed to write to file");
            fclose(file);
            return EXIT_FAILURE;
        }
    }

    size_t remaining_bytes = FILE_SIZE % sizeof(buffer);
    if (remaining_bytes > 0) {
        if (fwrite(buffer, remaining_bytes, 1, file) != 1) {
            perror("Failed to write remaining bytes to file");
            fclose(file);
            return EXIT_FAILURE;
        }
    }

    fclose(file);
    printf("Dummy file successfully created.\n");
    return EXIT_SUCCESS;
}