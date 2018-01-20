#include <stdio.h>
#include <stdlib.h>

char *readFile(char *filename) {
    FILE *f = fopen(filename, "rt");

    if (f == NULL) {
        puts("Cannot open file.");
        exit(2);
    }

    fseek(f, 0, SEEK_END);
    long length = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buffer = (char *) malloc(length + 1);
    buffer[length] = '\0';
    fread(buffer, 1, length, f);
    fclose(f);

    return buffer;
}

int main() {
    char *content = readFile("file.txt");
    puts(content);
    return 0;
}
