#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>
#include <vector>
#include <random>
using namespace std;

class RBTree {
private:
    enum Color { RED, BLACK };

    struct Node {
        int data;
        Node* left;
        Node* right;
        Node* parent;
        Color color;

        Node(int value) : data(value), left(nullptr), right(nullptr),
            parent(nullptr), color(RED) {
        }
    };

    Node* root;
    Node* nil;
    void leftRotate(Node* x);
    void rightRotate(Node* y);
    void insertFixup(Node* z);
    void deleteFixup(Node* x);
    void transplant(Node* u, Node* v);
    Node* minimum(Node* node);
    void destroyTree(Node* node);

    void inorderRecursive(Node* node);
    void preorderRecursive(Node* node);
    void postorderRecursive(Node* node);

    int treeHeight(Node* node);
    void printLevel(Node* node, int level, int indent);
    void printNodeInfo(Node* node);

public:
    RBTree();
    ~RBTree();

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

    bool isEmpty() const { return root == nil; }
};

#endif
