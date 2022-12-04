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
    char line1[128] = {0};
    char line2[128] = {0};
    char line3[128] = {0};

    if ((fp = fopen(INPUT_FILE_PATH, "r")) == NULL) {
        fprintf(stderr, "Can't find %s\n", INPUT_FILE_PATH);
        return EXIT_FAILURE;
    }

    while((read = getline(&line, &len, fp)) != -1) {
        if (line1[0] == 0) {
            strncpy(line1, line, read);
        } else if (line2[0] == 0) {
            strncpy(line2, line, read);
        } else if (line3[0] == 0) {
            strncpy(line3, line, read);
        }

        if (line1[0] != 0 && line2[0] != 0 && line3[0] != 0) {
            char itemMatch = '\0';

            for (int i = 0; line1[i] != '\0'; i++) {
                if (itemMatch != '\0')
                    break;
                for (int j = 0; line2[j] != '\0'; j++) {
                    if (itemMatch != '\0')
                        break;
                    else if (line1[i] != line2[j])
                        continue;
                    for (int k = 0; line3[k] != '\0'; k++) {
                        if (line3[k] == line2[j]) {
                            itemMatch = line3[k];
                            break;
                        }
                    }
                }
            }

            assert(isalpha(itemMatch));
            solution += calcItemPriority(itemMatch);
            memset(line1, 0, sizeof line1);
            memset(line2, 0, sizeof line2);
            memset(line3, 0, sizeof line3);
        }
    }

    printf("solution: %d\n", solution);

    // cleanup
    fclose(fp);
    free(line);
    return EXIT_SUCCESS;
}
