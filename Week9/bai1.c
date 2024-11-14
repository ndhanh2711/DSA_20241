#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct FileNode {
    char name[256];           // Tên file
    long size;                // Kích thước file
    long timestamp;           // Thời gian tạo file
    struct FileNode* next;    // Con trỏ đến node tiếp theo
} FileNode;
void insertFile(FileNode** head, char* name, long size, long timestamp) {
    FileNode* newNode = (FileNode*)malloc(sizeof(FileNode));
    strcpy(newNode->name, name);
    newNode->size = size;
    newNode->timestamp = timestamp;
    newNode->next = NULL;

    if (*head == NULL || (*head)->timestamp > timestamp) {
        newNode->next = *head;
        *head = newNode;
    } else {
        FileNode* current = *head;
        while (current->next != NULL && current->next->timestamp <= timestamp) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}
long calculateTotalSize(FileNode* head) {
    long totalSize = 0;
    FileNode* current = head;
    while (current != NULL) {
        totalSize += current->size;
        current = current->next;
    }
    return totalSize;
}
void backupToUSB(FileNode** head, long maxSize) {
    long currentSize = calculateTotalSize(*head);

    while (currentSize > maxSize) {
        // Tìm file có kích thước nhỏ nhất để loại bỏ
        FileNode* smallestPrev = NULL;
        FileNode* smallestNode = *head;
        FileNode* current = *head;
        while (current->next != NULL) {
            if (current->next->size < smallestNode->size) {
                smallestPrev = current;
                smallestNode = current->next;
            }
            current = current->next;
        }

        if (smallestPrev != NULL) {
            smallestPrev->next = smallestNode->next;
        } else {
            *head = smallestNode->next;
        }
        currentSize -= smallestNode->size;
        free(smallestNode);
    }
}
int main() {
    FileNode* head = NULL;
    // Thêm các file vào danh sách
    insertFile(&head, "file1.txt", 500000, 1627890000);
    insertFile(&head, "file2.txt", 150000, 1627893600);
    insertFile(&head, "file3.txt", 800000, 1627897200);
    // Tính tổng kích thước các file
    printf("Total size: %ld bytes\n", calculateTotalSize(head));
    // Sao lưu vào USB có kích thước 32GB (32 * 1024 * 1024 * 1024 bytes)
    backupToUSB(&head, 32L * 1024 * 1024 * 1024);
    // In lại danh sách sau khi sao lưu
    FileNode* current = head;
    while (current != NULL) {
        printf("File: %s, Size: %ld bytes\n", current->name, current->size);
        current = current->next;
    }
    return 0;
}
