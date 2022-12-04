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

int main(void) {
    FILE *fp = NULL;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int solution = 0;

    if ((fp = fopen(INPUT_FILE_PATH, "r")) == NULL) {
        fprintf(stderr, "Can't find %s\n", INPUT_FILE_PATH);
        return EXIT_FAILURE;
    }

    while((read = getline(&line, &len, fp)) != -1) {
        const int firstHalfStart = 0;
        const int firstHalfEnd = (read - 1) / 2;
        const int secondHalfStart = firstHalfEnd;
        const int secondHalfEnd = read - 1;
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
        solution += calcItemPriority(itemMatch);
    }

    printf("solution: %d\n", solution);

    // cleanup
    fclose(fp);
    free(line);
    return EXIT_SUCCESS;
}
