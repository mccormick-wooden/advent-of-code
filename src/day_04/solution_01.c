#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

const char *INPUT_FILE_PATH = "input.txt";

void fileIterator(FILE *fp, void (*callback)(), void *cbkretptr) {
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int lineNumber = 0;

    rewind(fp);
    while((read = getline(&line, &len, fp)) != -1) {
        if (callback != NULL) {
            (*callback)(line, read, lineNumber, cbkretptr);
            lineNumber++;
        }
    }
    free(line); // gets malloc'd in getline so we have to free
    rewind(fp);
}

int main(void) {
    FILE *fp = NULL;
    if ((fp = fopen(INPUT_FILE_PATH, "r")) == NULL) {
        printf("Can't find %s\n", INPUT_FILE_PATH);
        return 1;
    }

    int prioritySum = 0;

    printf("solution: %d\n", prioritySum);

    // cleanup
    fclose(fp);
    return 0;
}
