#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct FileNode {
    char name[256];          // Tên file
    long size;               // Kích thước file
    long timestamp;          // Thời gian lưu file
    struct FileNode* next;   // Con trỏ đến node tiếp theo
} FileNode;
void insertFile(FileNode** head, char* name, long size, long timestamp) {
    FileNode* newNode = (FileNode*)malloc(sizeof(FileNode));
    strcpy(newNode->name, name);
    newNode->size = size;
    newNode->timestamp = timestamp;
    newNode->next = NULL;

    if (*head == NULL || (*head)->size > size) {
        newNode->next = *head;
        *head = newNode;
    } else {
        FileNode* current = *head;
        while (current->next != NULL && current->next->size <= size) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}
void deleteSmallestOldestFiles(FileNode** head, long maxSize) {
    long currentSize = 0;
    FileNode* current = *head;

    // Tính tổng kích thước các file
    while (current != NULL) {
        currentSize += current->size;
        current = current->next;
    }

    // Xóa file nếu kích thước tổng vượt quá maxSize
    while (*head != NULL && currentSize > maxSize) {
        FileNode* smallestPrev = NULL;
        FileNode* smallestNode = *head;
        current = *head;

        // Tìm file có dung lượng nhỏ nhất và thời gian lưu lâu nhất
        while (current->next != NULL) {
            if (current->next->size < smallestNode->size || 
               (current->next->size == smallestNode->size && current->next->timestamp < smallestNode->timestamp)) {
                smallestPrev = current;
                smallestNode = current->next;
            }
            current = current->next;
        }

        // Xóa file nhỏ nhất và thời gian lưu lâu nhất
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
    insertFile(&head, "file2.txt", 150000, 1627883600);
    insertFile(&head, "file3.txt", 800000, 1627887200);
    insertFile(&head, "file4.txt", 500000, 1627891000);
    insertFile(&head, "file5.txt", 200000, 1627886000);

    // In danh sách trước khi xóa
    printf("Danh sách trước khi xóa:\n");
    FileNode* current = head;
    while (current != NULL) {
        printf("File: %s, Size: %ld bytes, Timestamp: %ld\n", current->name, current->size, current->timestamp);
        current = current->next;
    }

    // Xóa file có dung lượng bé nhất và thời gian lưu lâu nhất
    deleteSmallestOldestFiles(&head, 1000000);

    // In danh sách sau khi xóa
    printf("\nDanh sách sau khi xóa:\n");
    current = head;
    while (current != NULL) {
        printf("File: %s, Size: %ld bytes, Timestamp: %ld\n", current->name, current->size, current->timestamp);
        current = current->next;
    }

    return 0;
}
