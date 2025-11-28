#include "BST.h"
#include <iostream>
#include <vector>
#include <random>
using namespace std;
BST::Node::Node(int value) : data(value), LeftChild(nullptr), RightChild(nullptr) {}
BST::Node::~Node() {
    delete LeftChild;
    delete RightChild;
}
BST::BST() : root(nullptr) {}
BST::~BST() {
    delete root;
}
void BST::insert(int value) {
    root = insert_recursive(root, value);
}

void BST::del(int num) {
    root = del_recursive(root, num);
}

void BST::fmin() {
    Node* current = root;
    if (current == nullptr) {
        cout << "Дерево пусто.\n";
        return;
    }
    while (current->LeftChild != nullptr) {
        current = current->LeftChild;
    }
    cout << "Минимальное значение в дереве: " << current->data << "\n";
}

void BST::fmax() {
    Node* current = root;
    if (current == nullptr) {
        cout << "Дерево пусто.\n";
        return;
    }
    while (current->RightChild != nullptr) {
        current = current->RightChild;
    }
    cout << "Максимальное значение в дереве: " << current->data << "\n";
}

void BST::levelorder() {
    cout << "\nОБХОД В ШИРИНУ с показом уровней:\n";
    cout << "================================\n";

    if (root == nullptr) {
        cout << "Дерево пустое\n";
        cout << "================================\n";
        return;
    }

    vector<Node*> currentLevel;
    currentLevel.push_back(root);
    int levelNum = 0;

    while (!currentLevel.empty()) {
        cout << "Уровень " << levelNum << ": ";
        vector<Node*> nextLevel;

        for (Node* node : currentLevel) {
            cout << "[" << node->data << "] ";

            if (node->LeftChild != nullptr) {
                nextLevel.push_back(node->LeftChild);
            }
            if (node->RightChild != nullptr) {
                nextLevel.push_back(node->RightChild);
            }
        }
        cout << endl;

        currentLevel = nextLevel;
        levelNum++;
    }
    cout << "================================\n";
}

void BST::levelorder_str() {
    cout << "Обход в ширину: ";

    if (root == nullptr) {
        cout << "Дерево пустое\n";
        return;
    }

    vector<Node*> currentLevel;
    currentLevel.push_back(root);

    while (!currentLevel.empty()) {
        vector<Node*> nextLevel;

        for (Node* node : currentLevel) {
            cout << node->data << " ";

            if (node->LeftChild != nullptr) {
                nextLevel.push_back(node->LeftChild);
            }
            if (node->RightChild != nullptr) {
                nextLevel.push_back(node->RightChild);
            }
        }
        currentLevel = nextLevel;
    }
    cout << endl;
}

void BST::create_random_tree() {
    random_device rd;
    mt19937 gen(rd());
    cout << "Введите количество элементов дерева: ";
    int count;
    cin >> count;
    int num;
    for (size_t i = 0; i < count; i++)
    {
        uniform_int_distribution<> distrib(1, 100);
        num = distrib(gen);
        insert(num);
    }
}

void BST::print_tree() {
    int h = tree_height(root);
    for (int level = 0; level < h; level++) {
        cout << "LEVEL " << level << ":\n";
        print_level(root, level, 8 * (h - level));
        cout << "\n\n";
    }
}

bool BST::search(int num) {
    Node* current = root;

    while (current != nullptr) {
        if (current->data == num) {
            return true;
        }
        else if (num < current->data) {
            current = current->LeftChild;
        }
        else {
            current = current->RightChild;
        }
    }
    return false;
}

void BST::inorder() {
    cout << "Прямой обход: ";
    inorder_recursive(root);
    cout << endl;
}

void BST::preorder() {
    cout << "Центрированный обход: ";
    preorder_recursive(root);
    cout << endl;
}

void BST::postorder() {
    cout << "Обратный обход: ";
    postorder_recursive(root);
    cout << endl;
}

int BST::tree_height(Node* node) {
    if (!node) return 0;
    return 1 + max(tree_height(node->LeftChild), tree_height(node->RightChild));
}

void BST::print_level(Node* node, int level, int indent) {
    if (level == 0) {
        if (node)
            cout << string(indent, ' ') << node->data;
        else
            cout << string(indent, ' ') << " ";
        return;
    }

    if (!node) {
        print_level(nullptr, level - 1, indent);
        print_level(nullptr, level - 1, indent);
        return;
    }

    print_level(node->LeftChild, level - 1, indent);
    print_level(node->RightChild, level - 1, indent);
}

void BST::inorder_recursive(Node* node) {
    if (node != nullptr) {
        inorder_recursive(node->LeftChild);
        cout << node->data << " ";
        inorder_recursive(node->RightChild);
    }
}

void BST::preorder_recursive(Node* node) {
    if (node != nullptr) {
        cout << node->data << " ";
        preorder_recursive(node->LeftChild);
        preorder_recursive(node->RightChild);
    }
}
void BST::postorder_recursive(Node* node) {
    if (node != nullptr) {
        postorder_recursive(node->LeftChild);
        postorder_recursive(node->RightChild);
        cout << node->data << " ";
    }
}
BST::Node* BST::del_recursive(Node* node, int value) {
    if (node == nullptr) {
        cout << "Значение " << value << " не найдено в дереве.\n";
        return node;
    }
    if (value < node->data) {
        node->LeftChild = del_recursive(node->LeftChild, value);
    }
    else if (value > node->data) {
        node->RightChild = del_recursive(node->RightChild, value);
    }
    else {
        if (node->LeftChild == nullptr) {
            Node* temp = node->RightChild;
            node->RightChild = nullptr;
            delete node;
            return temp;
        }
        else if (node->RightChild == nullptr) {
            Node* temp = node->LeftChild;
            node->LeftChild = nullptr;
            delete node;
            return temp;
        }
        Node* temp = node->RightChild;
        while (temp && temp->LeftChild != nullptr) {
            temp = temp->LeftChild;
        }
        node->data = temp->data;
        node->RightChild = del_recursive(node->RightChild, temp->data);
    }
    cout << "Значение " << value << " удалено из дерева.\n";
    return node;
}
BST::Node* BST::insert_recursive(Node* node, int value) {
    if (node == nullptr) {
        return new Node(value);
    }
    if (value < node->data) {
        node->LeftChild = insert_recursive(node->LeftChild, value);
    }
    else if (value > node->data) {
        node->RightChild = insert_recursive(node->RightChild, value);
    }
    return node;
}