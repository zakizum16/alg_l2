#include "RB.h"

RBTree::RBTree() {
    nil = new Node(0);
    nil->color = BLACK;
    nil->left = nil->right = nil->parent = nil;
    root = nil;
}

RBTree::~RBTree() {
    destroyTree(root);
    delete nil;
}

void RBTree::destroyTree(Node* node) {
    if (node != nil) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

void RBTree::leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;

    if (y->left != nil) {
        y->left->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == nil) {
        root = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

void RBTree::rightRotate(Node* y) {
    Node* x = y->left;
    y->left = x->right;

    if (x->right != nil) {
        x->right->parent = y;
    }

    x->parent = y->parent;

    if (y->parent == nil) {
        root = x;
    }
    else if (y == y->parent->right) {
        y->parent->right = x;
    }
    else {
        y->parent->left = x;
    }

    x->right = y;
    y->parent = x;
}

void RBTree::insertFixup(Node* z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;

            if (y->color == RED) {
                
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->right) {
                
                    z = z->parent;
                    leftRotate(z);
                }
    
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        }
        else {
            Node* y = z->parent->parent->left;

            if (y->color == RED) {
               
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->left) {
                    
                    z = z->parent;
                    rightRotate(z);
                }
             
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void RBTree::insert(int value) {
    Node* z = new Node(value);
    Node* y = nil;
    Node* x = root;

    while (x != nil) {
        y = x;
        if (z->data < x->data) {
            x = x->left;
        }
        else if (z->data > x->data) {
            x = x->right;
        }
        else {
           
            delete z;
            return;
        }
    }

    z->parent = y;

    if (y == nil) {
        root = z;
    }
    else if (z->data < y->data) {
        y->left = z;
    }
    else {
        y->right = z;
    }

    z->left = nil;
    z->right = nil;
    z->color = RED;

    insertFixup(z);
    cout << "Элемент " << value << " добавлен в красно-черное дерево." << endl;
}

void RBTree::transplant(Node* u, Node* v) {
    if (u->parent == nil) {
        root = v;
    }
    else if (u == u->parent->left) {
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

RBTree::Node* RBTree::minimum(Node* node) {
    while (node->left != nil) {
        node = node->left;
    }
    return node;
}

void RBTree::deleteFixup(Node* x) {
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;

            if (w->color == RED) {
                // Case 1
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }

            if (w->left->color == BLACK && w->right->color == BLACK) {
           
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->right->color == BLACK) {
                   
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        }
        else {
            Node* w = x->parent->left;

            if (w->color == RED) {
                
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                w = x->parent->left;
            }

            if (w->right->color == BLACK && w->left->color == BLACK) {
                
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->left->color == BLACK) {
                 
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

void RBTree::remove(int value) {
    Node* z = root;
    while (z != nil) {
        if (value == z->data) {
            break;
        }
        else if (value < z->data) {
            z = z->left;
        }
        else {
            z = z->right;
        }
    }

    if (z == nil) {
        cout << "Значение " << value << " не найдено в дереве." << endl;
        return;
    }

    Node* y = z;
    Node* x;
    Color y_original_color = y->color;

    if (z->left == nil) {
        x = z->right;
        transplant(z, z->right);
    }
    else if (z->right == nil) {
        x = z->left;
        transplant(z, z->left);
    }
    else {
        y = minimum(z->right);
        y_original_color = y->color;
        x = y->right;

        if (y->parent == z) {
            x->parent = y;
        }
        else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (y_original_color == BLACK) {
        deleteFixup(x);
    }

    delete z;
    cout << "Значение " << value << " удалено из дерева." << endl;
}

bool RBTree::search(int value) {
    Node* current = root;
    while (current != nil) {
        if (current->data == value) {
            return true;
        }
        else if (value < current->data) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    return false;
}

void RBTree::inorderRecursive(Node* node) {
    if (node != nil) {
        inorderRecursive(node->left);
        cout << node->data << "(" << (node->color == RED ? "R" : "B") << ") ";
        inorderRecursive(node->right);
    }
}

void RBTree::preorderRecursive(Node* node) {
    if (node != nil) {
        cout << node->data << "(" << (node->color == RED ? "R" : "B") << ") ";
        preorderRecursive(node->left);
        preorderRecursive(node->right);
    }
}

void RBTree::postorderRecursive(Node* node) {
    if (node != nil) {
        postorderRecursive(node->left);
        postorderRecursive(node->right);
        cout << node->data << "(" << (node->color == RED ? "R" : "B") << ") ";
    }
}

void RBTree::inorder() {
    cout << "Центрированный обход: ";
    inorderRecursive(root);
    cout << endl;
}

void RBTree::preorder() {
    cout << "Прямой обход: ";
    preorderRecursive(root);
    cout << endl;
}

void RBTree::postorder() {
    cout << "Обратный обход: ";
    postorderRecursive(root);
    cout << endl;
}

void RBTree::levelorder() {
    cout << "\nОБХОД В ШИРИНУ с показом уровней:\n";
    cout << "================================\n";

    if (root == nil) {
        cout << "Дерево пустое\n";
        cout << "================================\n";
        return;
    }

    vector<Node*> currentLevel;
    currentLevel.push_back(root);
    int levelNum = 0;
	bool NoNilNodes = true;    
        
    while (NoNilNodes) {
        cout << "Уровень " << levelNum << ": ";
        vector<Node*> nextLevel;
		NoNilNodes = false;    
        for (Node* node : currentLevel) {
            if (node == nil) {
                cout << "[NIL(B)] ";
                nextLevel.push_back(nil);
                nextLevel.push_back(nil);
            }
            else {
                cout << "[" << node->data << "(" << (node->color == RED ? "R" : "B") << ")] ";
                nextLevel.push_back(node->left);
                nextLevel.push_back(node->right);
                if (node->left != nil || node->right != nil) {
                    NoNilNodes = true;
                }
            }
        }
        cout << endl;

        currentLevel = nextLevel;
        levelNum++;
        if (levelNum > 10) break;
    }
    cout << "================================\n";
}

void RBTree::levelorderStr() {
    cout << "Обход в ширину: ";

    if (root == nil) {
        cout << "Дерево пустое\n";
        return;
    }

    vector<Node*> currentLevel;
    currentLevel.push_back(root);

    while (!currentLevel.empty()) {
        vector<Node*> nextLevel;

        for (Node* node : currentLevel) {
            cout << node->data << "(" << (node->color == RED ? "R" : "B") << ") ";

            if (node->left != nil) {
                nextLevel.push_back(node->left);
            }
            if (node->right != nil) {
                nextLevel.push_back(node->right);
            }
        }
        currentLevel = nextLevel;
    }
    cout << endl;
}

void RBTree::findMin() {
    if (root == nil) {
        cout << "Дерево пусто.\n";
        return;
    }
    Node* minNode = minimum(root);
    cout << "Минимальное значение в дереве: " << minNode->data
        << "(" << (minNode->color == RED ? "R" : "B") << ")\n";
}

void RBTree::findMax() {
    if (root == nil) {
        cout << "Дерево пусто.\n";
        return;
    }
    Node* current = root;
    while (current->right != nil) {
        current = current->right;
    }
    cout << "Максимальное значение в дереве: " << current->data
        << "(" << (current->color == RED ? "R" : "B") << ")\n";
}

void RBTree::createRandomTree() {
    random_device rd;
    mt19937 gen(rd());
    cout << "Введите количество элементов дерева: ";
    int count;
    cin >> count;
    destroyTree(root);
    root = nil;

    for (int i = 0; i < count; i++) {
        uniform_int_distribution<> distrib(1, 100);
        int num = distrib(gen);
        insert(num);
    }
}

int RBTree::treeHeight(Node* node) {
    if (node == nil) return 0;
    return 1 + max(treeHeight(node->left), treeHeight(node->right));
}

void RBTree::printNodeInfo(Node* node) {
    if (node == nil) {
        cout << "NIL(B)";
    }
    else {
        cout << node->data << "(" << (node->color == RED ? "R" : "B") << ")";
    }
}

void RBTree::printLevel(Node* node, int level, int indent) {
    if (level == 0) {
        if (node != nil) {
            cout << string(indent, ' ');
            printNodeInfo(node);
        }
        else {
            cout << string(indent, ' ') << " ";
        }
        return;
    }

    if (node == nil) {
        printLevel(nil, level - 1, indent);
        printLevel(nil, level - 1, indent);
        return;
    }

    printLevel(node->left, level - 1, indent);
    printLevel(node->right, level - 1, indent);
}

void RBTree::printTree() {
    int h = treeHeight(root);
    for (int level = 0; level < h; level++) {
        cout << "LEVEL " << level << ":\n";
        printLevel(root, level, 8 * (h - level));
        cout << "\n\n";
    }
}