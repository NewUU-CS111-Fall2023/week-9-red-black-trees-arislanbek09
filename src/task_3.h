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
    void fixDeletion(Node* x, Node* xParent, bool isLeftChild);
    void insertFix(Node* z);
    void deleteFix(Node* x, Node* xParent, bool isLeftChild);
    Node* minimumNode(Node* start);
    void transplant(Node* u, Node* v);
    void deleteNode(Node* z);
    void printTree(Node* root, int space);

public:
    RedBlackTree() : root(nullptr) {}

    void Insert(int data);
    void Delete(int data);
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

void RedBlackTree::fixDeletion(Node* x, Node* xParent, bool isLeftChild) {
    while (x != root && (x == nullptr || x->color == BLACK)) {
        Node* w = (isLeftChild ? xParent->right : xParent->left);

        if (w != nullptr && w->color == RED) {
            w->color = BLACK;
            xParent->color = RED;
            if (isLeftChild) {
                rotateLeft(xParent);
                w = xParent->right;
            } else {
                rotateRight(xParent);
                w = xParent->left;
            }
        }

        if ((w->left == nullptr || w->left->color == BLACK) &&
            (w->right == nullptr || w->right->color == BLACK)) {
            w->color = RED;
            x = xParent;
            xParent = x->parent;
            isLeftChild = (xParent != nullptr && x == xParent->left);
        } else {
            if (isLeftChild && (w->right == nullptr || w->right->color == BLACK)) {
                if (w->left != nullptr) {
                    w->left->color = BLACK;
                }
                w->color = RED;
                rotateRight(w);
                w = xParent->right;
            } else if (!isLeftChild && (w->left == nullptr || w->left->color == BLACK)) {
                if (w->right != nullptr) {
                    w->right->color = BLACK;
                }
                w->color = RED;
                rotateLeft(w);
                w = xParent->left;
            }

            w->color = xParent->color;
            xParent->color = BLACK;
            if (isLeftChild) {
                if (w->right != nullptr) {
                    w->right->color = BLACK;
                }
                rotateLeft(xParent);
            } else {
                if (w->left != nullptr) {
                    w->left->color = BLACK;
                }
                rotateRight(xParent);
            }
            x = root;
        }
    }
    if (x != nullptr) {
        x->color = BLACK;
    }
}

void RedBlackTree::deleteFix(Node* x, Node* xParent, bool isLeftChild) {
    fixDeletion(x, xParent, isLeftChild);
}

void RedBlackTree::transplant(Node* u, Node* v) {
    if (u->parent == nullptr) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != nullptr) {
        v->parent = u->parent;
    }
}

void RedBlackTree::deleteNode(Node* z) {
    Node* y = z;
    Node* x;
    Color yOriginalColor = y->color;

    if (z->left == nullptr) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == nullptr) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = minimumNode(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            if (x != nullptr) {
                x->parent = y;
            }
        } else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (yOriginalColor == BLACK) {
        deleteFix(x, y->parent, (y == y->parent->left));
    }

    delete z;
}

Node* RedBlackTree::minimumNode(Node* start) {
    Node* current = start;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
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

void RedBlackTree::Delete(int data) {
    Node* z = root;
    while (z != nullptr) {
        if (data < z->data) {
            z = z->left;
        } else if (data > z->data) {
            z = z->right;
        } else {
            deleteNode(z);
            return;
        }
    }
}

void RedBlackTree::printTree() {
    printTree(root, 0);
}

void RedBlackTree::printTree(Node* root, int space) {
    if (root == nullptr) {
        return;
    }

    space += 4;

    printTree(root->right, space);

    std::cout << std::endl;
    for (int i = 4; i < space; i++) {
        std::cout << " ";
    }

    if (root->color == RED) {
        std::cout << root->data << "(RED)";
    } else {
        std::cout << root->data << "(BLACK)";
    }

    printTree(root->left, space);
}

int main() {
    RedBlackTree tree;

    int N, value;
    std::cout << "Enter the number of nodes (N): ";
    std::cin >> N;

    std::cout << "Enter the values of nodes: ";
    for (int i = 0; i < N; ++i) {
        std::cin >> value;
        tree.Insert(value);
    }

    std::cout << "Red-Black Tree:" << std::endl;
    tree.printTree();

    std::cout << "\nEnter a node value to delete: ";
    std::cin >> value;
    tree.Delete(value);

    std::cout << "\nRed-Black Tree after deletion:" << std::endl;
    tree.printTree();

    return 0;
}
