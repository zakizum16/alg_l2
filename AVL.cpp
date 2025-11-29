#include "AVL.h"

AVLTree::AVLTree() : root(nullptr) {}

AVLTree::AVLTree(const AVLTree& other) : root(nullptr) {
    copyTree(root, other.root);
}

AVLTree& AVLTree::operator=(const AVLTree& other) {
    if (this != &other) {
        destroyTree(root);
        root = nullptr;
        copyTree(root, other.root);
    }
    return *this;
}

AVLTree::~AVLTree() {
    destroyTree(root);
}

void AVLTree::copyTree(Node*& dest, Node* src) {
    if (src == nullptr) {
        dest = nullptr;
        return;
    }

    dest = new Node(src->data);
    dest->height = src->height;
    copyTree(dest->left, src->left);
    copyTree(dest->right, src->right);
}

void AVLTree::destroyTree(Node* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

int AVLTree::getHeight(Node* node) {
    return node ? node->height : 0;
}

int AVLTree::getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

AVLTree::Node* AVLTree::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

AVLTree::Node* AVLTree::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

AVLTree::Node* AVLTree::insertRecursive(Node* node, int value) {
    
    if (node == nullptr) {
        return new Node(value);
    }

    if (value < node->data) {
        node->left = insertRecursive(node->left, value);
    }
    else if (value > node->data) {
        node->right = insertRecursive(node->right, value);
    }
    else {
        return node; 
    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

    if (balance > 1 && value < node->left->data) {
        return rotateRight(node);
    }

    if (balance < -1 && value > node->right->data) {
        return rotateLeft(node);
    }

    if (balance > 1 && value > node->left->data) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && value < node->right->data) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void AVLTree::insert(int value) {
    root = insertRecursive(root, value);
}

AVLTree::Node* AVLTree::minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

AVLTree::Node* AVLTree::deleteRecursive(Node* node, int value) {
    if (node == nullptr) {
        cout << "Значение " << value << " не найдено в дереве.\n";
        return node;
    }

    if (value < node->data) {
        node->left = deleteRecursive(node->left, value);
    }
    else if (value > node->data) {
        node->right = deleteRecursive(node->right, value);
    }
    else {
        
        if (node->left == nullptr || node->right == nullptr) {
            Node* temp = node->left ? node->left : node->right;

            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            }
            else {
                *node = *temp; 
                temp->left = temp->right = nullptr;
            }
            delete temp;
        }
        else {
       
            Node* temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = deleteRecursive(node->right, temp->data);
        }
    }

  
    if (node == nullptr) {
        return node;
    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

  
    if (balance > 1 && getBalance(node->left) >= 0) {
        return rotateRight(node);
    }

    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && getBalance(node->right) <= 0) {
        return rotateLeft(node);
    }

    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    cout << "Значение " << value << " удалено из дерева.\n";
    return node;
}

void AVLTree::remove(int value) {
    root = deleteRecursive(root, value);
}

bool AVLTree::search(int value) {
    Node* current = root;
    while (current != nullptr) {
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

void AVLTree::inorderRecursive(Node* node) {
    if (node != nullptr) {
        inorderRecursive(node->left);
        cout << node->data << " ";
        inorderRecursive(node->right);
    }
}

void AVLTree::preorderRecursive(Node* node) {
    if (node != nullptr) {
        cout << node->data << " ";
        preorderRecursive(node->left);
        preorderRecursive(node->right);
    }
}

void AVLTree::postorderRecursive(Node* node) {
    if (node != nullptr) {
        postorderRecursive(node->left);
        postorderRecursive(node->right);
        cout << node->data << " ";
    }
}

void AVLTree::inorder() {
    cout << "Центрированный обход: ";
    inorderRecursive(root);
    cout << endl;
}

void AVLTree::preorder() {
    cout << "Прямой обход: ";
    preorderRecursive(root);
    cout << endl;
}

void AVLTree::postorder() {
    cout << "Обратный обход: ";
    postorderRecursive(root);
    cout << endl;
}

void AVLTree::levelorder() {
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

            if (node->left != nullptr) {
                nextLevel.push_back(node->left);
            }
            if (node->right != nullptr) {
                nextLevel.push_back(node->right);
            }
        }
        cout << endl;

        currentLevel = nextLevel;
        levelNum++;
    }
    cout << "================================\n";
}

void AVLTree::levelorderStr() {
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

            if (node->left != nullptr) {
                nextLevel.push_back(node->left);
            }
            if (node->right != nullptr) {
                nextLevel.push_back(node->right);
            }
        }
        currentLevel = nextLevel;
    }
    cout << endl;
}

void AVLTree::findMin() {
    Node* current = root;
    if (current == nullptr) {
        cout << "Дерево пусто.\n";
        return;
    }
    while (current->left != nullptr) {
        current = current->left;
    }
    cout << "Минимальное значение в дереве: " << current->data << "\n";
}

void AVLTree::findMax() {
    Node* current = root;
    if (current == nullptr) {
        cout << "Дерево пусто.\n";
        return;
    }
    while (current->right != nullptr) {
        current = current->right;
    }
    cout << "Максимальное значение в дереве: " << current->data << "\n";
}

void AVLTree::createRandomTree() {
    random_device rd;
    mt19937 gen(rd());
    cout << "Введите количество элементов дерева: ";
    int count;
    cin >> count;

    destroyTree(root);
    root = nullptr;

    for (int i = 0; i < count; i++) {
        uniform_int_distribution<> distrib(1, 100);
        int num = distrib(gen);
        insert(num);
    }
}

int AVLTree::treeHeight(Node* node) {
    if (!node) return 0;
    return node->height;
}

void AVLTree::printLevel(Node* node, int level, int indent) {
    if (level == 0) {
        if (node)
            cout << string(indent, ' ') << node->data << "(" << node->height << ")";
        else
            cout << string(indent, ' ') << " ";
        return;
    }

    if (!node) {
        printLevel(nullptr, level - 1, indent);
        printLevel(nullptr, level - 1, indent);
        return;
    }

    printLevel(node->left, level - 1, indent);
    printLevel(node->right, level - 1, indent);
}

void AVLTree::printTree() {
    int h = treeHeight(root);
    for (int level = 0; level < h; level++) {
        cout << "LEVEL " << level << ":\n";
        printLevel(root, level, 8 * (h - level));
        cout << "\n\n";
    }
}