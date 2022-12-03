// --- Day 3: Rucksack Reorganization ---

// One Elf has the important job of loading all of the rucksacks with supplies for the jungle journey. Unfortunately, that
// Elf didn't quite follow the packing instructions, and so a few items now need to be rearranged.

// Each rucksack has two large compartments. All items of a given type are meant to go into exactly one of the two
// compartments. The Elf that did the packing failed to follow this rule for exactly one item type per rucksack.

// The Elves have made a list of all of the items currently in each rucksack (your puzzle input), but they need your help
//  finding the errors. Every item type is identified by a single lowercase or uppercase letter (that is, a and A refer to
//   different types of items).

// The list of items for each rucksack is given as characters all on a single line. A given rucksack always has the same
//  number of items in each of its two compartments, so the first half of the characters represent items in the first
//   compartment, while the second half of the characters represent items in the second compartment.

// For example, suppose you have the following list of contents from six rucksacks:

// vJrwpWtwJgWrhcsFMMfFFhFp
// jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL
// PmmdzqPrVvPwwTWBwg
// wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn
// ttgJtRGJQctTZtZT
// CrZsJsPPZsGzwwsLwLmpwMDw

//     - The first rucksack contains the items vJrwpWtwJgWrhcsFMMfFFhFp, which means its first compartment contains
//         the items vJrwpWtwJgWr, while the second compartment contains the items hcsFMMfFFhFp. The only item type that
//         appears in both compartments is lowercase p.
//     - The second rucksack's compartments contain jqHRNqRjqzjGDLGL and rsFMfFZSrLrFZsSL. The only item type that
//         appears in both compartments is uppercase L.
//     - The third rucksack's compartments contain PmmdzqPrV and vPwwTWBwg; the only common item type is uppercase P.
//     - The fourth rucksack's compartments only share item type v.
//     - The fifth rucksack's compartments only share item type t.
//     - The sixth rucksack's compartments only share item type s.

// To help prioritize item rearrangement, every item type can be converted to a priority:

//     Lowercase item types a through z have priorities 1 through 26.
//     Uppercase item types A through Z have priorities 27 through 52.

// In the above example, the priority of the item type that appears in both compartments of each rucksack is
// 16 (p), 38 (L), 42 (P), 22 (v), 20 (t), and 19 (s); the sum of these is 157.

// Find the item type that appears in both compartments of each rucksack. What is the sum of the priorities
// of those item types?

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
