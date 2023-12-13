#include <iostream>

class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    TreeNode* root;

    int countChildren(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }

        int leftChild = countChildren(node->left);
        int rightChild = countChildren(node->right);

        return leftChild + rightChild + 1;
    }

public:
    BinaryTree() : root(nullptr) {}

    void insert(int data) {
        root = insertRecursive(root, data);
    }

    TreeNode* insertRecursive(TreeNode* node, int data) {
        if (node == nullptr) {
            return new TreeNode(data);
        }

        if (data < node->data) {
            node->left = insertRecursive(node->left, data);
        } else if (data > node->data) {
            node->right = insertRecursive(node->right, data);
        }

        return node;
    }

    void displayChildrenCount() {
        displayChildrenCountRecursive(root);
    }

    void displayChildrenCountRecursive(TreeNode* node) {
        if (node != nullptr) {
            int childrenCount = countChildren(node) - 1;  // subtract 1 to exclude the current node
            std::cout << node->data << " - " << childrenCount << std::endl;
            displayChildrenCountRecursive(node->left);
            displayChildrenCountRecursive(node->right);
        }
    }
}
