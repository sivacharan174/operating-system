#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 50
#define MAX_FILENAME_LENGTH 20
#define MAX_SUBDIRECTORIES 10
#define MAX_SUBDIR_NAME_LENGTH 20

struct File {
    char filename[MAX_FILENAME_LENGTH];
};

struct SubDirectory {
    char name[MAX_SUBDIR_NAME_LENGTH];
    struct File files[MAX_FILES];
    int fileCount;
};

struct Directory {
    struct SubDirectory subDirectories[MAX_SUBDIRECTORIES];
    int subDirCount;
};

void initializeDirectory(struct Directory *dir) {
    dir->subDirCount = 0;
}

void addSubDirectory(struct Directory *dir, const char *subDirName) {
    if (dir->subDirCount < MAX_SUBDIRECTORIES) {
        strcpy(dir->subDirectories[dir->subDirCount].name, subDirName);
        dir->subDirectories[dir->subDirCount].fileCount = 0;
        dir->subDirCount++;
        printf("Subdirectory '%s' added to directory.\n", subDirName);
    } else {
        printf("Max subdirectories reached. Cannot add '%s'\n", subDirName);
    }
}

void addFile(struct Directory *dir, const char *subDirName, const char *filename) {
    for (int i = 0; i < dir->subDirCount; i++) {
        if (strcmp(dir->subDirectories[i].name, subDirName) == 0) {
            if (dir->subDirectories[i].fileCount < MAX_FILES) {
                strcpy(dir->subDirectories[i].files[dir->subDirectories[i].fileCount].filename, filename);
                dir->subDirectories[i].fileCount++;
                printf("File '%s' added to subdirectory '%s'\n", filename, subDirName);
                return;
            } else {
                printf("Subdirectory is full. Cannot add '%s' to '%s'\n", filename, subDirName);
                return;
            }
        }
    }
    printf("Subdirectory '%s' not found. File '%s' cannot be added.\n", subDirName, filename);
}

void displayFiles(struct Directory *dir) {
    printf("Subdirectories and files in the directory:\n");
    for (int i = 0; i < dir->subDirCount; i++) {
        printf("Subdirectory: %s\n", dir->subDirectories[i].name);
        printf("Files: ");
        for (int j = 0; j < dir->subDirectories[i].fileCount; j++) {
            printf("%s ", dir->subDirectories[i].files[j].filename);
        }
        printf("\n");
    }
}

int main() {
    struct Directory twoLevelDirectory;
    initializeDirectory(&twoLevelDirectory);

    addSubDirectory(&twoLevelDirectory, "Documents");
    addSubDirectory(&twoLevelDirectory, "Pictures");

    addFile(&twoLevelDirectory, "Documents", "file1.txt");
    addFile(&twoLevelDirectory, "Documents", "report.doc");
    addFile(&twoLevelDirectory, "Pictures", "image.jpg");
    addFile(&twoLevelDirectory, "Documents", "notes.txt");

    displayFiles(&twoLevelDirectory);

    return 0;
}
