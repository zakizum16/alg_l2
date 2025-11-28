#ifndef BST_H
#define BST_H

#include <iostream>
#include <vector>
#include <random>
using namespace std;

class BST {
private:
    struct Node {
        int data;
        Node* LeftChild;
        Node* RightChild;
        Node(int value);
        ~Node();
    };
    Node* root;

    int tree_height(Node* node);
    void print_level(Node* node, int level, int indent);
    void inorder_recursive(Node* node);
    void preorder_recursive(Node* node);
    void postorder_recursive(Node* node);
    Node* del_recursive(Node* node, int value);
    Node* insert_recursive(Node* node, int value);

public:
    BST();
    ~BST();

    void insert(int value);
    void del(int num);
    void fmin();
    void fmax();
    void levelorder();
    void levelorder_str();
    void create_random_tree();
    void print_tree();
    bool search(int num);
    void inorder();
    void preorder();
    void postorder();
};

#endif