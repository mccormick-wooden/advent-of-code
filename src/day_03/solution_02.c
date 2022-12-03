// --- Part Two ---

// As you finish identifying the misplaced items, the Elves come to you with another issue.

// For safety, the Elves are divided into groups of three. Every Elf carries a badge that identifies their group.
// For efficiency, within each group of three Elves, the badge is the only item type carried by all three Elves.
// That is, if a group's badge is item type B, then all three Elves will have item type B somewhere in their rucksack,
// and at most two of the Elves will be carrying any other item type.

// The problem is that someone forgot to put this year's updated authenticity sticker on the badges. All of the badges
// need to be pulled out of the rucksacks so the new authenticity stickers can be attached.

// Additionally, nobody wrote down which item type corresponds to each group's badges. The only way to tell which item type
// is the right one is by finding the one item type that is common between all three Elves in each group.

// Every set of three lines in your list corresponds to a single group, but each group can have a different badge item type.
// So, in the above example, the first group's rucksacks are the first three lines:

// vJrwpWtwJgWrhcsFMMfFFhFp
// jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL
// PmmdzqPrVvPwwTWBwg

// And the second group's rucksacks are the next three lines:

// wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn
// ttgJtRGJQctTZtZT
// CrZsJsPPZsGzwwsLwLmpwMDw

// In the first group, the only item type that appears in all three rucksacks is lowercase r; this must be their badges. In the
// second group, their badge item type must be Z.

// Priorities for these items must still be found to organize the sticker attachment efforts: here, they are 18 (r) for the first
// group and 52 (Z) for the second group. The sum of these is 70.

// Find the item type that corresponds to the badges of each three-Elf group. What is the sum of the priorities of those item types?

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
