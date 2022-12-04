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

void calcPriority_itercbk(char *line1, ssize_t lineLength1,
                            char *line2, ssize_t lineLength2,
                            char *line3, ssize_t lineLength3, int lineNumber, void *returnptr) {

    char itemMatch = '\0';

    for (int i = 0; i<lineLength1-1; i++) {
        if (itemMatch != '\0')
            break;
        for (int j = 0; j<lineLength2-1; j++) {
            if (itemMatch != '\0')
                break;
            else if (line1[i] != line2[j])
                continue;
            for (int k = 0; k<lineLength3-1; k++) {
                if (line3[k] == line2[j]) {
                    itemMatch = line3[k];
                    break;
                }
            }
        }
    }

    assert(isalpha(itemMatch));
    (*(int*)returnptr) = (*(int*)returnptr) + calcItemPriority(itemMatch);
}

void fileIterator(FILE *fp, void (*callback)(), void *cbkretptr) {
    rewind(fp);
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int lineNumber = 0;

    char line1[128];
    char line2[128];
    char line3[128];
    memset(line1, 0, sizeof line1);
    memset(line2, 0, sizeof line2);
    memset(line3, 0, sizeof line3);
    ssize_t lineLength1 = 0;
    ssize_t lineLength2 = 0;
    ssize_t lineLength3 = 0;

    while((read = getline(&line, &len, fp)) != -1) {
        if (line1[0] == 0) {
            strncpy(line1, (const char*)line, read);
            lineLength1 = read;
        } else if (line2[0] == 0) {
            strncpy(line2, (const char*)line, read);
            lineLength2 = read;
        } else if (line3[0] == 0) {
            strncpy(line3, (const char*)line, read);
            lineLength3 = read;
        }

        if (callback != NULL && line1[0] != 0 && line2[0] != 0 && line3[0] != 0) {
            (*callback)(line1, lineLength1, line2, lineLength2, line3, lineLength3, lineNumber, cbkretptr);
            lineNumber++;

            memset(line1, 0, sizeof line1);
            memset(line2, 0, sizeof line2);
            memset(line3, 0, sizeof line3);
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
    fileIterator(fp, &calcPriority_itercbk, &prioritySum);

    printf("solution: %d\n", prioritySum);

    // cleanup
    fclose(fp);
    return 0;
}
