#include <iostream>

enum Color { RED, BLACK };

class Node {
public:
    int data;
    Color color;
    Node* parent;
    Node* left;
    Node* right;

    Node(int value, Color c = RED, Node* p = nullptr, Node* l = nullptr, Node* r = nullptr)
            : data(value), color(c), parent(p), left(l), right(r) {}
};

class RedBlackTree {
private:
    Node* root;

    void rotateLeft(Node* x);
    void rotateRight(Node* y);
    void leftRotate(Node* x);
    void rightRotate(Node* y);
    void fixInsertion(Node* z);
    void insertFix(Node* z);
    void reverseInorderTraversal(Node* root);
    void printTree(Node* root, int space);

public:
    RedBlackTree() : root(nullptr) {}

    void Insert(int data);
    void printTree();
};

void RedBlackTree::rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != nullptr) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void RedBlackTree::rotateRight(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    if (x->right != nullptr) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == nullptr) {
        root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
}

void RedBlackTree::leftRotate(Node* x) {
    if (x == nullptr || x->right == nullptr)
        return;

    Node* y = x->right;
    x->right = y->left;
    if (y->left != nullptr) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void RedBlackTree::rightRotate(Node* y) {
    if (y == nullptr || y->left == nullptr)
        return;

    Node* x = y->left;
    y->left = x->right;
    if (x->right != nullptr) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == nullptr) {
        root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
}

void RedBlackTree::fixInsertion(Node* z) {
    while (z != root && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;
            if (y != nullptr && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    rotateLeft(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotateRight(z->parent->parent);
            }
        } else {
            Node* y = z->parent->parent->left;
            if (y != nullptr && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rotateRight(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotateLeft(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void RedBlackTree::insertFix(Node* z) {
    fixInsertion(z);
}

void RedBlackTree::reverseInorderTraversal(Node* root) {
    if (root != nullptr) {
        reverseInorderTraversal(root->right);

        std::cout << "(" << root->data;
        if (root->color == RED) {
            std::cout << "(RED)";
        } else {
            std::cout << "(BLACK)";
        }
        reverseInorderTraversal(root->left);
        std::cout << ")";
    }
}

void RedBlackTree::printTree() {
    reverseInorderTraversal(root);
    std::cout << std::endl;
}

void RedBlackTree::printTree(Node* root, int space) {
    // Unchanged, you can keep the existing printTree method here if needed
}

void RedBlackTree::Insert(int data) {
    Node* z = new Node(data);
    Node* y = nullptr;
    Node* x = root;

    while (x != nullptr) {
        y = x;
        if (z->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    z->parent = y;
    if (y == nullptr) {
        root = z;
    } else if (z->data < y->data) {
        y->left = z;
    } else {
        y->right = z;
    }

    insertFix(z);
}
