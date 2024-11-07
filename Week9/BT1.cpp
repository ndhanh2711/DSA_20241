#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

// chèn một node mới 
void insertAfter(Node* T, int newData) {
    if (T == nullptr) {
        cout << "Node T không tồn tại!" << endl;
        return;
    }

    Node* newNode = new Node();
    newNode->data = newData;
    newNode->next = T->next;
    T->next = newNode;
}

//  xoá node cuối
void deleteTail(Node*& head) {
    if (head == nullptr) {
        cout << "Danh sách rỗng!" << endl;
        return;
    }

    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        return;
    }

    Node* current = head;
    while (current->next->next != nullptr) {
        current = current->next;
    }

    delete current->next;
    current->next = nullptr;
}

// xoá node 
void deleteNode(Node*& head, Node* T) {
    if (T == nullptr) {
        cout << "Node T không tồn tại!" << endl;
        return;
    }

    if (T->next == nullptr) {
        // Nếu T là node cuối,  xoá T
        if (head == T) {
            delete head;
            head = nullptr;
        } else {
            Node* current = head;
            while (current->next != T) {
                current = current->next;
            }
            current->next = nullptr;
            delete T;
        }
    } else {
        Node* temp = T->next;
        T->data = temp->data;
        T->next = temp->next;
        delete temp;
    }
}

// Hàm thêm node vào đầu
void insertAtHead(Node*& head, int newData) {
    Node* newNode = new Node();
    newNode->data = newData;
    newNode->next = head;
    head = newNode;
}

// hiển thị danh sách
void printList(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}

// kiểm tra
int main() {
    Node* head = nullptr;

    // Thêm phần tử vào danh sách
    insertAtHead(head, 10);
    insertAtHead(head, 20);
    insertAtHead(head, 30);
    insertAtHead(head, 40);

    cout << "Danh sách ban đầu: ";
    printList(head);

    // chèn node sau node (giá trị 40)
    cout << "Chèn 25 sau node đầu tiên (40): ";
    insertAfter(head, 25);
    printList(head);

    // Xoá node cuối
    cout << "Xoá node đuôi: ";
    deleteTail(head);
    printList(head);

    // Xoá node giữa, node được trỏ bởi head->next (node có giá trị 25)
    cout << "Xoá node có giá trị 25: ";
    deleteNode(head, head->next);
    printList(head);

    return 0;
}
