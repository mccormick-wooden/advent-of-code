#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static const char* INPUT_FILE_PATH = "input.txt";
static const int EMPTY = -1;

typedef struct CrateStack {
    char stack[8];
    int topIndex;
} CrateStack_t;

CrateStack_t* initCrateStacks(FILE* file) {
    CrateStack_t* cs = calloc(9, sizeof(CrateStack_t));

    for (int i = 0; i < 9; i++) { cs[i].topIndex = EMPTY; }

    // file processing

    rewind(file);
    return cs;
}

int isEmpty(CrateStack_t* cs) {
    return cs->topIndex == EMPTY;
}

int isFull(CrateStack_t* cs) {
    return cs->topIndex == (int)sizeof(cs->stack) + EMPTY;
}

char pop(CrateStack_t* cs) {
    assert(!isEmpty(cs));

    char crate = cs->stack[cs->topIndex];
    cs->stack[cs->topIndex] = 0;
    cs->topIndex--;
    return crate;
}

void push(CrateStack_t* cs, char crate) {
    assert(!isFull(cs));

    cs->stack[cs->topIndex + 1] = crate;
    cs->topIndex++;
}

int main(void) {
    FILE* fp = NULL;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int solution = 0;

    if ((fp = fopen(INPUT_FILE_PATH, "r")) == NULL) {
        fprintf(stderr, "Can't find %s\n", INPUT_FILE_PATH);
        return EXIT_FAILURE;
    }

    CrateStack_t* cs = initCrateStacks(fp);

    while((read = getline(&line, &len, fp)) != -1) {

    }

    printf("solution: %d\n", solution);

    // cleanup
    fclose(fp);
    free(line);
    free(cs);
    return EXIT_SUCCESS;
}
