#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 50
#define MAX_FILENAME_LENGTH 20

struct File {
    char filename[MAX_FILENAME_LENGTH];
};

struct Directory {
    struct File files[MAX_FILES];
    int fileCount;
};

void initializeDirectory(struct Directory *dir) {
    dir->fileCount = 0;
}

void addFile(struct Directory *dir, const char *filename) {
    if (dir->fileCount < MAX_FILES) {
        strcpy(dir->files[dir->fileCount].filename, filename);
        dir->fileCount++;
        printf("File '%s' added to directory.\n", filename);
    } else {
        printf("Directory is full. Cannot add '%s'\n", filename);
    }
}

void displayFiles(struct Directory *dir) {
    printf("Files in the directory:\n");
    for (int i = 0; i < dir->fileCount; i++) {
        printf("%s\n", dir->files[i].filename);
    }
}

int main() {
    struct Directory singleLevelDirectory;
    initializeDirectory(&singleLevelDirectory);

    addFile(&singleLevelDirectory, "file1.txt");
    addFile(&singleLevelDirectory, "document.doc");
    addFile(&singleLevelDirectory, "image.jpg");
    addFile(&singleLevelDirectory, "notes.txt");
    addFile(&singleLevelDirectory, "report.pdf");

    displayFiles(&singleLevelDirectory);

    return 0;
}
