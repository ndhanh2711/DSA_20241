#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

struct FileInfo {
    char name[50];
    long size;
};

void createFile(const char *fileName, long fileSize) {
    FILE *file = fopen(fileName, "wb");
    if (file == NULL) {
        perror("Error creating file");
        return;
    }

    for (long i = 0; i < fileSize; i++) {
        fputc(rand() % 256, file);
    }
    fclose(file);
}

void swap(struct FileInfo *a, struct FileInfo *b) {
    struct FileInfo temp = *a;
    *a = *b;
    *b = temp;
}

void selectionSort(struct FileInfo files[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (files[j].size < files[minIndex].size) {
                minIndex = j;
            }
        }
        swap(&files[i], &files[minIndex]);
    }
}

void printFiles(struct FileInfo files[], int n) {
    printf("Files sorted by size (ascending):\n");
    for (int i = 0; i < n; i++) {
        printf("%s: %ld bytes\n", files[i].name, files[i].size);
    }
}

int main() {
    srand(time(0));

    int fileCount = 5;
    struct FileInfo files[fileCount];
    
    for (int i = 0; i < fileCount; i++) {
        sprintf(files[i].name, "file_%d.txt", i + 1);
        files[i].size = rand() % 1000 + 500;
        createFile(files[i].name, files[i].size);
        printf("Created %s with size %ld bytes\n", files[i].name, files[i].size);
    }

    struct stat st;
    for (int i = 0; i < fileCount; i++) {
        if (stat(files[i].name, &st) == 0) {
            files[i].size = st.st_size;
        } else {
            perror("Error getting file size");
        }
    }

    selectionSort(files, fileCount);
    printFiles(files, fileCount);

    return 0;
}
