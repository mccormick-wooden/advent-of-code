#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

static const char *INPUT_FILE_PATH = "input.txt";

typedef struct dirNode {
    char id[256];
    struct dirNode* parentDir;
    struct dirNode* firstChildDir;
    struct dirNode* nextSiblingDir;
    int size;
} dirNode_t;

bool isLineCommand(const char* line) {
    return line[0] == '$';
}

bool isLineDir(const char* line) {
    return strncmp(line, "dir", 3) == 0;
}

void sanitizeLine(char* line) {
    memset(strchr(line, '\n'), '\0', 1);
}

char* getCommand(const char* line, char* buffer) {
    strncpy(buffer, line+2, 3);
    return buffer;
}

dirNode_t* callocDirNode() {
    return calloc(1, sizeof(dirNode_t));
}

dirNode_t* initRoot(FILE* fp) {
    char buffer[1024];
    fgets(buffer, sizeof(buffer), fp);
    fseek(fp, strlen(buffer), SEEK_SET);
    dirNode_t* root = callocDirNode();
    root->id[0] = '/';
    return root;
}

dirNode_t* getRoot(dirNode_t* cwd) {
    while (cwd->parentDir != NULL)
        cwd = cwd->parentDir;

    return cwd;
}

void freeTree(dirNode_t* cwd) {
    if (cwd->firstChildDir != NULL)
        freeTree(cwd->firstChildDir);
    if (cwd->nextSiblingDir != NULL)
        freeTree(cwd->nextSiblingDir);
    free(cwd);
}

void freeAllDir(dirNode_t* cwd) {
    dirNode_t* root = getRoot(cwd);
    freeTree(root);
}

void setId(dirNode_t* node, const char* line) {
    strcpy(node->id, line+4);
}

void buildChild(dirNode_t* parent, const char* line) {
    dirNode_t* child = callocDirNode();
    setId(child, line);
    child->parentDir = parent;
    parent->firstChildDir = child;

printf("            BUILDING FIRST CHILD UNDER %s: %s\n",child->parentDir->id, parent->firstChildDir->id);

}

void buildNextSibling(dirNode_t* cwd, const char* line) {
    dirNode_t* lastChildSibling = cwd->firstChildDir;
    while (lastChildSibling->nextSiblingDir != NULL)
        lastChildSibling = lastChildSibling->nextSiblingDir;

    dirNode_t* nextSibling = callocDirNode();
    setId(nextSibling, line);
    nextSibling->parentDir = lastChildSibling->parentDir;
    lastChildSibling->nextSiblingDir = nextSibling;
printf("            BUILDING SIBLING ADJ TO %s: %s\n",lastChildSibling->id, lastChildSibling->nextSiblingDir->id);
}

void buildDir(dirNode_t* cwd, const char* line) {
    if (cwd->firstChildDir == NULL) {
        buildChild(cwd, line);
    } else {
        buildNextSibling(cwd, line);
    }
}

dirNode_t* findDir(dirNode_t* cwd, const char* dirName) { // THE WAY THIS WORKS MAY NOT BE A SAFE ASSUMPTION
    dirNode_t* child = cwd->firstChildDir;
    while (strcmp(child->id, dirName) != 0) {
        child = child->nextSiblingDir;
    }
    return child;
    // cwd = getRoot(cwd);
    // return findDirInTree(cwd, dirName);
}

int sumTree(dirNode_t* cwd) {
    int fileSizes = 0;
    if (cwd->firstChildDir != NULL)
        fileSizes += sumTree(cwd->firstChildDir);
    if (cwd->nextSiblingDir != NULL)
        fileSizes += sumTree(cwd->nextSiblingDir);


    // if (cwd->summedLocalFileSizes <= 100000) {
    //     return fileSizes + cwd->summedLocalFileSizes;
    // } else {
    //     return fileSizes;
    // }

    return fileSizes + cwd->size;
}

int sumAllDir(dirNode_t* cwd) {
    dirNode_t* root = getRoot(cwd);
    return sumTree(root);
}

dirNode_t* processCommand(const char* line, dirNode_t* cwd, bool* lsMode) {
    char command[3];
    getCommand(line, command);

    if (strncmp(command, "ls", 2) == 0) {
        *lsMode = true;
    } else if (strncmp(command, "cd", 2) == 0 && line[5] == '.') {
        cwd = cwd->parentDir;
    } else {
        char buffer[256] = {0};
        strcpy(buffer, line+5);
        //printf("%s\n", buffer);
        cwd = findDir(cwd, buffer);
    }
    //printf("%s\n", command);
    // TODO

    return cwd;
}

int main(void) {
    FILE *fp = NULL;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    bool lsMode = false;

    if ((fp = fopen(INPUT_FILE_PATH, "r")) == NULL) {
        fprintf(stderr, "Can't find %s\n", INPUT_FILE_PATH);
        return EXIT_FAILURE;
    }

    dirNode_t* cwd = initRoot(fp);

    while ((read = getline(&line, &len, fp)) != -1) {

        sanitizeLine(line);

printf("PROCESSING: %s\n", line);

        if (isLineCommand(line)) {
            cwd = processCommand(line, cwd, &lsMode);
        } else if (lsMode) {
            if (isLineCommand(line)) {
                lsMode = false;
                cwd = processCommand(line, cwd, &lsMode);
            } else if (isLineDir(line)) {
                buildDir(cwd, line);
            } else { // file
                int fileSize;
                assert(sscanf(line, "%d ", &fileSize) == 1);
printf("            ADDING SIZE TO %s: %d\n", cwd->id, fileSize);

                cwd->size += fileSize;
            }
        }
    }

    printf("solution: %d\n", sumAllDir(cwd));

    // cleanup
    fclose(fp);
    free(line);
    freeAllDir(cwd);
    return EXIT_SUCCESS;
}



    // dirNode_t* child121 = callocDirNode();
    // dirNode_t* child111 = callocDirNode();
    // dirNode_t* child12 = callocDirNode(); child12->firstChildDir = child121;
    // dirNode_t* child11 = callocDirNode(); child11->firstChildDir = child111; child11->nextSiblingDir = child12;
