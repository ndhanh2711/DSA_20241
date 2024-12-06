#include <iostream>
#include <stack>
#include <cstring>
struct TreeNode {
    std::string data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const std::string& val) : data(val), left(nullptr), right(nullptr) {}
};

int operatorPrecedence(char op) {
    switch (op) {
        case '^': return 3;
        case '*': 
        case '/': return 2;
        case '+': 
        case '-': return 1;
        default: return 0;
    }
}

TreeNode* constructExpressionTree(const std::string& expression) {
    std::string sanitizedExpr;
    for (char ch : expression) {
        if (ch != ' ') sanitizedExpr += ch;
    }

    std::stack<TreeNode*> operandStack;
    std::stack<char> operatorStack;

    for (size_t i = 0; i < sanitizedExpr.length(); ++i) {
        if (isdigit(sanitizedExpr[i]) || sanitizedExpr[i] == '.') {
            std::string number;
            bool hasDot = false;

            while (i < sanitizedExpr.length() &&
                   (isdigit(sanitizedExpr[i]) || sanitizedExpr[i] == '.')) {
                if (sanitizedExpr[i] == '.') {
                    if (hasDot) break;
                    hasDot = true;
                }
                number += sanitizedExpr[i++];
            }
            --i;

            operandStack.push(new TreeNode(number));
        } else if (isalpha(sanitizedExpr[i])) {
            std::string variable;
            while (i < sanitizedExpr.length() && isalpha(sanitizedExpr[i])) {
                variable += sanitizedExpr[i++];
            }
            --i;

            operandStack.push(new TreeNode(variable));
        } else if (sanitizedExpr[i] == '(') {
            operatorStack.push(sanitizedExpr[i]);
        } else if (sanitizedExpr[i] == ')') {
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                char op = operatorStack.top();
                operatorStack.pop();

                TreeNode* right = operandStack.top();
                operandStack.pop();
                TreeNode* left = operandStack.top();
                operandStack.pop();

                TreeNode* node = new TreeNode(std::string(1, op));
                node->left = left;
                node->right = right;

                operandStack.push(node);
            }
            if (!operatorStack.empty() && operatorStack.top() == '(')
                operatorStack.pop();
        } else if (strchr("+-*/^", sanitizedExpr[i])) {
            while (!operatorStack.empty() &&
                   operatorStack.top() != '(' &&
                   operatorPrecedence(operatorStack.top()) >= operatorPrecedence(sanitizedExpr[i])) {
                char op = operatorStack.top();
                operatorStack.pop();

                TreeNode* right = operandStack.top();
                operandStack.pop();
                TreeNode* left = operandStack.top();
                operandStack.pop();

                TreeNode* node = new TreeNode(std::string(1, op));
                node->left = left;
                node->right = right;

                operandStack.push(node);
            }
            operatorStack.push(sanitizedExpr[i]);
        }
    }

    while (!operatorStack.empty()) {
        char op = operatorStack.top();
        operatorStack.pop();

        TreeNode* right = operandStack.top();
        operandStack.pop();
        TreeNode* left = operandStack.top();
        operandStack.pop();

        TreeNode* node = new TreeNode(std::string(1, op));
        node->left = left;
        node->right = right;

        operandStack.push(node);
    }

    return operandStack.top();
}

void traversePreOrder(TreeNode* root) {
    if (!root) return;

    std::cout << root->data << " ";
    traversePreOrder(root->left);
    traversePreOrder(root->right);
}

void traverseInOrder(TreeNode* root) {
    if (!root) return;

    traverseInOrder(root->left);
    std::cout << root->data << " ";
    traverseInOrder(root->right);
}

void traversePostOrder(TreeNode* root) {
    if (!root) return;

    traversePostOrder(root->left);
    traversePostOrder(root->right);
    std::cout << root->data << " ";
}

void freeTree(TreeNode* root) {
    if (!root) return;

    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

int main() {
    std::string expression = "a + 5 * b / c - c ^ 8 + d * e ^ 0.5";

    TreeNode* root = constructExpressionTree(expression);

    std::cout << "Pre-order traversal: ";
    traversePreOrder(root);
    std::cout << "\nIn-order traversal: ";
    traverseInOrder(root);
    std::cout << "\nPost-order traversal: ";
    traversePostOrder(root);
    std::cout << "\n";

    freeTree(root);

    return 0;
}
