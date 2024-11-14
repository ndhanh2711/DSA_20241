#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Định nghĩa cấu trúc một node
typedef struct Node {
    char word[256];        // Từ trong câu
    int count;             // Số lần xuất hiện của từ
    struct Node* next;     // Con trỏ đến node tiếp theo
} Node;
void addWord(Node** head, char* word) {
    Node* current = *head;
    Node* prev = NULL;

    // Tìm xem từ đã tồn tại trong danh sách chưa
    while (current != NULL && strcmp(current->word, word) != 0) {
        prev = current;
        current = current->next;
    }

    // Nếu từ đã tồn tại, tăng số đếm
    if (current != NULL) {
        current->count += 1;
    } else {
        // Nếu từ chưa tồn tại, thêm mới
        Node* newNode = (Node*)malloc(sizeof(Node));
        strcpy(newNode->word, word);
        newNode->count = 1;
        newNode->next = NULL;
        
        if (prev == NULL) {
            *head = newNode;
        } else {
            prev->next = newNode;
        }
    }
}
Node* findMostFrequentWord(Node* head) {
    Node* current = head;
    Node* mostFrequent = head;
    
    while (current != NULL) {
        if (current->count > mostFrequent->count) {
            mostFrequent = current;
        }
        current = current->next;
    }
    
    return mostFrequent;
}
void removeReduplicativeWords(Node* head) {
    Node* current = head;
    
    while (current != NULL && current->next != NULL) {
        if (strcmp(current->word, current->next->word) == 0) {
            Node* temp = current->next;
            current->next = current->next->next;
            free(temp);
        } else {
            current = current->next;
        }
    }
}
int countUniqueWords(Node* head) {
    int count = 0;
    Node* current = head;
    
    while (current != NULL) {
        count += 1;
        current = current->next;
    }
    
    return count;
}
int main() {
    Node* head = NULL;
    char sentence[] = "mưa rơi rơi trên phố nhỏ mưa rơi trên phố lớn";
    char* word = strtok(sentence, " ");

    // Thêm các từ vào danh sách liên kết
    while (word != NULL) {
        addWord(&head, word);
        word = strtok(NULL, " ");
    }

    // Xác định từ xuất hiện nhiều nhất
    Node* mostFrequent = findMostFrequentWord(head);
    printf("Most frequent word: %s (%d times)\n", mostFrequent->word, mostFrequent->count);

    // Loại bỏ từ láy
    removeReduplicativeWords(head);

    // Đếm số từ vựng
    int uniqueWordsCount = countUniqueWords(head);
    printf("Unique words count: %d\n", uniqueWordsCount);

    // In danh sách các từ còn lại
    Node* current = head;
    while (current != NULL) {
        printf("%s (%d times)\n", current->word, current->count);
        current = current->next;
    }

    return 0;
}
