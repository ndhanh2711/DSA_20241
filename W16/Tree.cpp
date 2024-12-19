#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Node {
    string name;
    int pageNumber;
    vector<Node*> children;

    Node(string name, int pageNumber) : name(name), pageNumber(pageNumber) {}
};

class Book {
private:
    Node* root;

public:
    Book(string name) {
        root = new Node(name, 0);
    }

    Node* getRoot() {
        return root;
    }

    void addNode(Node* parent, string name, int pageNumber) {
        Node* newNode = new Node(name, pageNumber);
        parent->children.push_back(newNode);
    }

    // Xác định số chương của cuốn sách
    int countChapters(Node* node) {
        if (node == nullptr) return 0;
        int count = 0;
        for (auto child : node->children) {
            count += countChapters(child);
        }
        return count + (node->children.size() > 0 ? 1 : 0);
    }

    // Tìm chương dài nhất của cuốn sách
    Node* findLongestChapter(Node* node, Node* &longestChapter, int &maxPages) {
        if (node == nullptr) return nullptr;
        int totalPages = node->pageNumber;
        for (auto child : node->children) {
            totalPages += child->pageNumber;
        }
        if (totalPages > maxPages) {
            maxPages = totalPages;
            longestChapter = node;
        }
        for (auto child : node->children) {
            findLongestChapter(child, longestChapter, maxPages);
        }
        return longestChapter;
    }

    // Thực hiện tìm một mục và xóa mục đó khỏi sách
    bool removeNode(Node* &parent, string name) {
        if (parent == nullptr) return false;
        for (auto it = parent->children.begin(); it != parent->children.end(); ++it) {
            if ((*it)->name == name) {
                delete *it;
                parent->children.erase(it);
                return true;
            }
            if (removeNode(*it, name)) return true;
        }
        return false;
    }

    // Cập nhật lại số trang của từng mục
    void updatePages(Node* node) {
        if (node == nullptr) return;
        for (auto child : node->children) {
            node->pageNumber += child->pageNumber;
            updatePages(child);
        }
    }
};

int main() {
    // Tạo cuốn sách và các mục lục
    Book myBook("My Book");
    Node* root = myBook.getRoot();
    myBook.addNode(root, "Chapter 1", 10);
    myBook.addNode(root, "Chapter 2", 20);
    myBook.addNode(root->children[0], "Section 1.1", 5);
    myBook.addNode(root->children[0], "Section 1.2", 8);
    myBook.addNode(root->children[1], "Section 2.1", 15);

    // Xác định số chương của cuốn sách
    cout << "Number of chapters: " << myBook.countChapters(root) << endl;

    // Tìm chương dài nhất
    Node* longestChapter = nullptr;
    int maxPages = 0;
    longestChapter = myBook.findLongestChapter(root, longestChapter, maxPages);
    if (longestChapter != nullptr) {
        cout << "Longest chapter: " << longestChapter->name << " with " << maxPages << " pages" << endl;
    }

    // Xóa một mục khỏi sách
    myBook.removeNode(root, "Section 1.2");
    myBook.updatePages(root);
    cout << "After removing Section 1.2, Chapter 1 pages: " << root->children[0]->pageNumber << endl;

    return 0;
}
