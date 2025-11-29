

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;
#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

class AVLTree {
private:
    struct Node {
        int data;
        Node* left;
        Node* right;
        int height;

        Node(int value) : data(value), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;
    int getHeight(Node* node);
    int getBalance(Node* node);
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    Node* insertRecursive(Node* node, int value);
    Node* deleteRecursive(Node* node, int value);
    Node* minValueNode(Node* node);
    void destroyTree(Node* node);
    void inorderRecursive(Node* node);
    void preorderRecursive(Node* node);
    void postorderRecursive(Node* node);
    int treeHeight(Node* node);
    void printLevel(Node* node, int level, int indent);
    void copyTree(Node*& dest, Node* src);

public:
    AVLTree();
    AVLTree(const AVLTree& other);
    AVLTree& operator=(const AVLTree& other);
    ~AVLTree();

    void insert(int value);
    void remove(int value);
    bool search(int value);

    void inorder();
    void preorder();
    void postorder();
    void levelorder();
    void levelorderStr();

    void findMin();
    void findMax();
    void createRandomTree();
    void printTree();

    bool isEmpty() const { return root == nullptr; }
};

#endif