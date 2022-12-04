#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

const char *INPUT_FILE_PATH = "input.txt";
const int ASCII_LOWER_OFFSET = -96;
const int ASCII_UPPER_OFFSET = 58 + ASCII_LOWER_OFFSET;

int calcItemPriority(char item) {
    int score = isupper(item) ? item + ASCII_UPPER_OFFSET : item + ASCII_LOWER_OFFSET;
    assert(score >= 1 && score <= 52);
    return score;
}

void calcPriority_itercbk(char *line, ssize_t lineLength, int lineNumber, void *returnptr) {
    int firstHalfStart = 0;
    int firstHalfEnd = (lineLength - 1) / 2;
    int secondHalfStart = firstHalfEnd;
    int secondHalfEnd = lineLength - 1;
    char itemMatch = '\0';

    for (int i = firstHalfStart; i < firstHalfEnd; i++) {
        if (itemMatch != '\0')
            break;
        for (int j = secondHalfStart; j < secondHalfEnd; j++) {
            if (line[i] == line[j]) {
                itemMatch = line[i];
                break;
            }
        }
    }

    assert(isalpha(itemMatch));
    (*(int*)returnptr) = (*(int*)returnptr) + calcItemPriority(itemMatch);
}

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

int main() {
    FILE *fp = NULL;
    if ((fp = fopen(INPUT_FILE_PATH, "r")) == NULL)
        return 1;

    int prioritySum = 0;
    fileIterator(fp, &calcPriority_itercbk, &prioritySum);

    printf("priority sum: %d\n", prioritySum);

    // cleanup
    fclose(fp);
    return 0;
}
