#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static const char* INPUT_FILE_PATH = "input.txt";
static const int EMPTY = -1;

typedef struct CrateStack {
    char stack[256];
    int topIndex;
} CrateStack_t;

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

char peek(CrateStack_t* cs) {
    return cs->stack[cs->topIndex];
}

void execMoveInstruction(int num, CrateStack_t* from, CrateStack_t* to) {
    while (num > 0) {
        push(to, pop(from));
        num--;
    }
}

CrateStack_t* initCrateStacks(FILE* fp) {
    CrateStack_t* cs = calloc(9, sizeof(CrateStack_t));
    for (int i = 0; i < 9; i++) { cs[i].topIndex = EMPTY; }

    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    const int STACK_LINE_OFFSET = 50;
    char stackLines[8*STACK_LINE_OFFSET] = {0};

    for (int i = 0; i < 8; i++) {
        read = getline(&line, &len, fp);
        strncpy(&stackLines[i*STACK_LINE_OFFSET], line, read);
    }

    for (int i = 7; i >= 0; i--) {
        int stack_offset = 1;
        for (int j = 0; j < 9; j++) {
            char crate = stackLines[i*STACK_LINE_OFFSET+stack_offset];
            if (crate != ' ') {
                push(&cs[j], crate);
            }

            stack_offset += 4;
        }
    }

    rewind(fp);
    free(line);
    return cs;
}

int main(void) {
    FILE* fp = NULL;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    if ((fp = fopen(INPUT_FILE_PATH, "r")) == NULL) {
        fprintf(stderr, "Can't find %s\n", INPUT_FILE_PATH);
        return EXIT_FAILURE;
    }

    CrateStack_t* cs = initCrateStacks(fp);

    int lineNumber = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        lineNumber++;
        if (lineNumber < 11) {
            continue; // Don't parse any crate stack info from top of the file
        }

        int numToMove, fromStackId, toStackId;
        assert(sscanf(line, "move %d from %d to %d", &numToMove, &fromStackId, &toStackId) == 3);

        execMoveInstruction(numToMove, &cs[fromStackId-1], &cs[toStackId-1]);
    }

    char solution[10] = {0};
    for (int i = 0; i < 9; i++) {
        solution[i] = peek(&cs[i]);
    }

    printf("solution: %s\n", solution);

    // cleanup
    fclose(fp);
    free(line);
    free(cs);
    return EXIT_SUCCESS;
}
