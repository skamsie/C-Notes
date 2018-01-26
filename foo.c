#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// save file contents to string pointer
char *readFile(char *filename) {
    FILE *f = fopen(filename, "rt");

    if (f == NULL) {
        puts("Cannot open file.");
        exit(-1);
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

typedef struct {
    char **elements;
    int length;
} splitArray;

splitArray split(char *str, char *delimiter) {
    char **array = NULL;
    char *p = strtok(str, delimiter);
    int n_spaces = 0;
    splitArray arr;

    while (p) {
      array = realloc (array, sizeof (char*) * ++n_spaces);

      if (array == NULL)
        exit (-1); /* memory allocation failed */

      size_t len = strlen(p);

      // strip newline if exists
      if (p[len - 1] == '\n') {
        p[--len] = '\0';
      }

      array[n_spaces - 1] = p;
      p = strtok(NULL, "::");
    }

    /* realloc one extra element for the last NULL */

    array = realloc (array, sizeof (char*) * (n_spaces + 1));
    array[n_spaces] = 0;

    arr.elements = array;
    arr.length = n_spaces;

    return arr;
}

int main() {
    char *str = readFile("file.txt");
    splitArray arr = split(str, "::");
    char **array = arr.elements;
    int column = arr.length;
    int i;

    for (i = 0; i < column; ++i)
      printf ("array[%d] = %s\n", i, array[i]);

    /* free the memory allocated */
    free (array);
    return 0;
}
