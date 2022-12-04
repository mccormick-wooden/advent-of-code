#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

const char *INPUT_FILE_PATH = "input.txt";

void solution_cbk(char *line, ssize_t read, int lineNumber, void *cbkptr) {
    // this is disgusting
    char tokBuffer[50] = {0}; // strtok modifies the original char array, so we copy to a buffer for safety
    strncpy(tokBuffer, line, read-1); // read - 1 to strip out the \n, probably a better way to do this upstream
    char *lh = strtok(tokBuffer, ",");
    int lhlower = atoi(strtok(lh, "-"));
    int lhupper = atoi(strtok(NULL, "-"));

    memset(tokBuffer, 0, sizeof(tokBuffer));
    strncpy(tokBuffer, line, read-1);
    strtok(tokBuffer, ",");
    char *rh = strtok(NULL, ",");
    int rhlower = atoi(strtok(rh, "-"));
    int rhupper = atoi(strtok(NULL, "-"));

    // atoi doesn't set errno or do anything with errors except return 0, so this wouldn't work if zeros were possible values
    assert(lhlower > 0);
    assert(lhupper > 0);
    assert(rhlower > 0);
    assert(rhupper > 0);

    if ((lhupper >= rhlower && lhupper <= rhupper) || (rhupper >= lhlower && rhupper <= lhupper)) {
        (*(int*)cbkptr)++;
    }
}

int enumerateFile(FILE *fp, void (*callback)(), void *cbkptr) {
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int lineNumber = 0;

    rewind(fp);
    while((read = getline(&line, &len, fp)) != -1) {
        lineNumber++;
        if (callback != NULL) {
            (*callback)(line, read, lineNumber, cbkptr);
        }
    }
    free(line); // gets malloc'd in getline so we have to free
    rewind(fp);
    return lineNumber;
}

int main(void) {
    FILE *fp = NULL;
    if ((fp = fopen(INPUT_FILE_PATH, "r")) == NULL) {
        printf("Can't find %s\n", INPUT_FILE_PATH);
        return 1;
    }

    int solution = 0;
    enumerateFile(fp, &solution_cbk, &solution);
    printf("solution: %d\n", solution);

    // cleanup
    fclose(fp);
    return 0;
}
