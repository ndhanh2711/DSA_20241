#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Định nghĩa cấu trúc một node
typedef struct Node {
    int data;               // Dữ liệu lưu trữ trong node
    struct Node* next;      // Con trỏ đến node tiếp theo
} Node;
void insertNode(Node** head, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = *head;
    *head = newNode;
}
void deleteHead(Node** head) {
    if (*head != NULL) {
        Node* temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

void deleteTail(Node** head) {
    if (*head == NULL) return;

    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
    } else {
        Node* current = *head;
        while (current->next->next != NULL) {
            current = current->next;
        }
        free(current->next);
        current->next = NULL;
    }
}

void deleteAfter(Node* prevNode) {
    if (prevNode != NULL && prevNode->next != NULL) {
        Node* temp = prevNode->next;
        prevNode->next = temp->next;
        free(temp);
    }
}
void menu() {
    printf("\nMenu:\n");
    printf("1. Thêm node vào danh sách\n");
    printf("2. Hiển thị danh sách\n");
    printf("3. Xóa node ở đầu danh sách\n");
    printf("4. Xóa node ở cuối danh sách\n");
    printf("5. Xóa node sau một node cho trước\n");
    printf("6. Thoát\n");
}

void displayList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}
int main() {
    Node* head = NULL;
    int choice, data, prevData;
    Node* current;

    do {
        menu();
        printf("Chọn một tùy chọn: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Nhập dữ liệu của node: ");
                scanf("%d", &data);
                insertNode(&head, data);
                break;
            case 2:
                displayList(head);
                break;
            case 3:
                deleteHead(&head);
                break;
            case 4:
                deleteTail(&head);
                break;
            case 5:
                printf("Nhập dữ liệu của node trước node cần xóa: ");
                scanf("%d", &prevData);
                current = head;
                while (current != NULL && current->data != prevData) {
                    current = current->next;
                }
                if (current != NULL) {
                    deleteAfter(current);
                } else {
                    printf("Không tìm thấy node có dữ liệu %d trong danh sách.\n", prevData);
                }
                break;
            case 6:
                printf("Thoát chương trình.\n");
                break;
            default:
                printf("Tùy chọn không hợp lệ.\n");
        }
    } while (choice != 6);

    return 0;
}
