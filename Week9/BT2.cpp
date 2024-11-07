#include <iostream>
using namespace std;

// Cấu trúc node cho danh sách liên kết
struct Node {
    int exponent;       // Số mũ của x
    int coefficient;    // Hệ số của x^exponent
    Node* next;
};

// Hàm tạo một node mới
Node* createNode(int exponent, int coefficient) {
    Node* newNode = new Node;
    newNode->exponent = exponent;
    newNode->coefficient = coefficient;
    newNode->next = nullptr;
    return newNode;
}

// Hàm thêm node vào danh sách theo thứ tự giảm dần của exponent
void insertNode(Node*& head, int exponent, int coefficient) {
    if (coefficient == 0) return;  // Bỏ qua nếu hệ số bằng 0

    Node* newNode = createNode(exponent, coefficient);

    // Trường hợp danh sách rỗng hoặc node mới có exponent lớn nhất
    if (!head || head->exponent < exponent) {
        newNode->next = head;
        head = newNode;
        return;
    }

    // Tìm vị trí chèn thích hợp
    Node* temp = head;
    while (temp->next && temp->next->exponent > exponent) {
        temp = temp->next;
    }

    // Nếu tìm thấy cùng số mũ, cộng hệ số
    if (temp->next && temp->next->exponent == exponent) {
        temp->next->coefficient += coefficient;
        if (temp->next->coefficient == 0) { // Xoá node nếu hệ số = 0
            Node* toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
        }
        delete newNode;
    } else {
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

// Hàm cộng hai đa thức
Node* addPolynomials(Node* poly1, Node* poly2) {
    Node* result = nullptr;

    while (poly1) {
        insertNode(result, poly1->exponent, poly1->coefficient);
        poly1 = poly1->next;
    }
    while (poly2) {
        insertNode(result, poly2->exponent, poly2->coefficient);
        poly2 = poly2->next;
    }

    return result;
}

// Hàm hiển thị đa thức
void printPolynomial(Node* poly) {
    bool first = true;
    while (poly) {
        if (!first && poly->coefficient > 0) {
            cout << " + ";
        } else if (poly->coefficient < 0) {
            cout << " - ";
        } else if (!first) {
            cout << " ";
        }

        if (poly->exponent == 0) {
            cout << abs(poly->coefficient);
        } else if (poly->exponent == 1) {
            cout << abs(poly->coefficient) << ".x";
        } else {
            cout << abs(poly->coefficient) << ".x^" << poly->exponent;
        }

        poly = poly->next;
        first = false;
    }
    cout << endl;
}

// Hàm xoá danh sách liên kết
void freePolynomial(Node* poly) {
    while (poly) {
        Node* temp = poly;
        poly = poly->next;
        delete temp;
    }
}

int main() {
    // Khởi tạo đa thức f(x) = 5.x^10 + 1
    Node* f = nullptr;
    insertNode(f, 10, 5);
    insertNode(f, 0, 1);

    // Khởi tạo đa thức g(x) = 10.x^15 - 2.x^7 + 3.x^2 - 7
    Node* g = nullptr;
    insertNode(g, 15, 10);
    insertNode(g, 7, -2);
    insertNode(g, 2, 3);
    insertNode(g, 0, -7);

    cout << "f(x) = ";
    printPolynomial(f);

    cout << "g(x) = ";
    printPolynomial(g);

    // Tính tổng h(x) = f(x) + g(x)
    Node* h = addPolynomials(f, g);
    cout << "h(x) = f(x) + g(x) = ";
    printPolynomial(h);

    // Giải phóng bộ nhớ
    freePolynomial(f);
    freePolynomial(g);
    freePolynomial(h);

    return 0;
}
