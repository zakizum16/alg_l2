// alg_l2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы. //
#include <iostream>
#include<random>
#include <unordered_set>

using namespace std;
class BST {
private:
    struct Node {
        int data;
        Node* LeftChild;
        Node* RightChild;
        Node(int value) :data(value), LeftChild(nullptr), RightChild(nullptr) {}
        ~Node() {
            delete LeftChild;
            delete RightChild;
            std::cout << "Удален Узел с data=" << data << std::endl;
        }
    };
    Node* root;
    int tree_height(Node* node) {
        if (!node) return 0;
        return 1 + max(tree_height(node->LeftChild), tree_height(node->RightChild));
    }
    void print_level(Node* node, int level, int indent) {
        if (level == 0) {
            // печатаем один узел
            if (node)
                cout << string(indent, ' ') << node->data;
            else
                cout << string(indent, ' ') << " ";
            return;
        }

        if (!node) {
            // если узла нет — рисуем пустые места сразу
            print_level(nullptr, level - 1, indent);
            print_level(nullptr, level - 1, indent);
            return;
        }

        print_level(node->LeftChild, level - 1, indent);
        print_level(node->RightChild, level - 1, indent);
    }
    Node* del_recursive(Node* node, int value) {
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
    Node* insert_recursive(Node* node, int value) {
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
    };
    void inorder(Node* node) {
     
        if (node != nullptr) {
            inorder(node->LeftChild);
            cout << node->data << " ";
            inorder(node->RightChild);
        }
    }
    void preorder(Node* node) { 
        if (node != nullptr) {
            cout << node->data << " ";
            preorder(node->LeftChild);
            preorder(node->RightChild);
        }
    }
    void postorder(Node* node) {
        if (node != nullptr) {
            postorder(node->LeftChild);
            postorder(node->RightChild);
            cout << node->data << " ";  
         
        }
    }

public:
    BST() :root(nullptr) {}
    ~BST() {
        delete root;
    }
    void print_inorder() {
        cout << "Центрированный обход :";
        inorder(root);
        cout << endl;
    }
    void print_preorder() {
        cout << "Прямой обход :";
        preorder(root);
        cout << endl;
    }
    void print_postorder() {
        cout << "Обратный обход :";
        postorder(root);
        cout << endl;
    }
    void insert(int value) {
        root = insert_recursive(root, value);
    }
    void del(int num) {
		root = del_recursive(root, num);


	}   
    void fmin() {
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
    void fmax() {
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
    void create_random_tree() {
        random_device rd;
        mt19937 gen(rd());

        cout << "Введите количество элементов дерева: ";
        int count;
        cin >> count;

		// гарантируем уникальность значений
        int range = max(count * 3, 100);
		//автоматически увеличиваем диапазон, если нужно больше уникальных чисел
        uniform_int_distribution<> distrib(1, range);

        unordered_set<int> unique_numbers;
		//дерево с уникальными значениями
        for (int i = 0; i < count; i++) {
            int num;
            do {
                num = distrib(gen);
            } while (unique_numbers.count(num) > 0);

            insert(num);
            unique_numbers.insert(num);
        }

        cout << "Дерево заполнено " << count << " уникальными элементами\n";
        cout << "Диапазон: 1-" << range << "\n";
    }
    void print_tree() {
        int h = tree_height(root);
        for (int level = 0; level < h; level++) {
            cout << "LEVEL " << level << ":\n";
            print_level(root, level, 8 * (h - level));
            cout << "\n\n";
        }
    }
    bool search(int num){
        Node* current = root;
        
        while (current != nullptr) {
            if (current->data == num) {
                return true;
            }
            else if (num < current->data) {
                current = current->LeftChild;  // Идем влево
            }
            else {
                current = current->RightChild; // Идем вправо
            }
        }
        return false;

       
    }
    void height() {
        cout << "Высота дерева: " << tree_height(root) << "\n";
	}
    
};
int main()
{
    system("chcp 65001 > nul");
    setlocale(LC_ALL, "RUS");
    cout << "                  АиСД лаба 2\n";
    cout<< "\n";
    cout << "\n";
    cout << "\n";
    int count;
    BST Tree;
    cout<<Tree.search(10)<<" - найдено/не найдено (1/0) \n";
   Tree.create_random_tree();
   Tree.print_tree();
   Tree.print_inorder();
   Tree.print_postorder();
   Tree.print_preorder();
   Tree.print_tree();
   



}
