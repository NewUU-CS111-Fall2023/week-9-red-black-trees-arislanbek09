/*
 * Author:
 * Date:
 * Name:
 */

#include <iostream>
#include "task_1.h"
#include "task_2.h"
#include "task_3.h"
#include "task_4.h"
#include "task_5.h"

int main() {
    std::cout << "Task 1" << std::endl;
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



    std::cout << "Task 2" << std::endl;
    RedBlackTree tree1;

    int N1, value1;
    std::cout << "Enter the number of nodes (N): ";
    std::cin >> N1;

    std::cout << "Enter the values of nodes: ";
    for (int i = 0; i < N1; ++i) {
        std::cin >> value1;
        tree.Insert(value1);
    }

    std::cout << "Red-Black Tree:" << std::endl;
    tree.printTree();



    std::cout << "Task 3" << std::endl;
    RedBlackTree tree2;

    int N2, value2;
    std::cout << "Enter the number of nodes (N): ";
    std::cin >> N2;

    std::cout << "Enter the values of nodes: ";
    for (int i = 0; i < N2; ++i) {
        std::cin >> value2;
        tree.Insert(value2);
    }

    std::cout << "Red-Black Tree:" << std::endl;
    tree.printTree();

    std::cout << "\nEnter a node value to delete: ";
    std::cin >> value2;
    tree.Delete(value2);

    std::cout << "\nRed-Black Tree after deletion:" << std::endl;
    tree.printTree();



    std::cout << "Task 4" << std::endl;

    RedBlackTree tree3;

    int N3, value3;
    std::cout << "Enter the number of nodes (N): ";
    std::cin >> N3;

    std::cout << "Enter the values of nodes: ";
    for (int i = 0; i < N3; ++i) {
        std::cin >> value3;
        tree.Insert(value3);
    }

    std::cout << "Red-Black Tree (Reversed):" << std::endl;
    tree.printTree();


    std::cout << "Task 5" << std::endl;
    BinaryTree tree5;

    int N5, value5;
    std::cout << "Enter the number of nodes (N): ";
    std::cin >> N5;

    std::cout << "Enter the values of nodes: ";
    for (int i = 0; i < N5; ++i) {
        std::cin >> value5;
        tree.insert(value5);
    }

    std::cout << "Node - Number of Children" << std::endl;
    tree.displayChildrenCount();
    
    
    
    return 0;
}
