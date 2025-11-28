
#include"BST.h"
#include"AVL.h"
#include <iostream>
using namespace std;
void checkBST()
{
    BST Tree;
    Tree.insert(50);
    Tree.insert(30);
    Tree.insert(70);
    Tree.insert(20);
    Tree.insert(40);
    Tree.insert(60);
    Tree.insert(80);
    Tree.insert(10);
    Tree.insert(25);
    // cout << "\n";
    // cout << "Поиск : " << Tree.search(10) << " (1-найдено, 0-не найдено)\n";
    cout << "\n";
    Tree.fmin();
    Tree.fmax();
    cout << "\n";
    Tree.inorder();
    Tree.preorder();
    Tree.postorder();
    cout << "\n";
    Tree.levelorder();
    Tree.levelorder_str();
    cout << "\n";
    Tree.print_tree();
    cout << "\n";
    Tree.del(30);
    Tree.levelorder();

}
void checkAVL() {
    AVLTree tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);
    tree.insert(10);
    tree.insert(25);
    tree.insert(35);
    tree.insert(45);
    cout << " ВИДЫ ОБХОДОВ:" << endl;
    tree.inorder();
    tree.preorder();
    tree.postorder();
    tree.levelorderStr();
    tree.levelorder();
    cout << "Поиск 40: " << (tree.search(40) ? "Найдено" : "Не найдено") << endl;
    cout << "Поиск 100: " << (tree.search(100) ? "Найдено" : "Не найдено") << endl;
    cout << "Поиск 25: " << (tree.search(25) ? "Найдено" : "Не найдено") << endl;
    tree.findMin();
    tree.findMax();

    tree.printTree();

    cout << "Удаляем 20:" << endl;
    tree.remove(20);
    tree.inorder();

    cout << "Удаляем 30:" << endl;
    tree.remove(30);
    tree.inorder();

    cout << "Удаляем 50:" << endl;
    tree.remove(50);
    tree.inorder();

    cout << " СОСТОЯНИЕ ПОСЛЕ УДАЛЕНИЯ:" << endl;
    tree.levelorder();
    tree.findMin();
    tree.findMax();

    cout << "ПРОВЕРКА БАЛАНСИРОВКИ:" << endl;
    AVLTree balanceTest;
    cout << "Добавляем для RL поворота: 10, 30, 20" << endl;
    balanceTest.insert(10);
    balanceTest.insert(30);
    balanceTest.insert(20);
    cout << "Результат: ";
    balanceTest.inorder();
    balanceTest.levelorder();
    AVLTree randomTree;

    cout << "Создаем дерево с 8 случайными элементами..." << endl;
    randomTree.insert(23);
    randomTree.insert(45);
    randomTree.insert(12);
    randomTree.insert(67);
    randomTree.insert(34);
    randomTree.insert(89);
    randomTree.insert(56);
    randomTree.insert(78);

    randomTree.inorder();
    randomTree.levelorder();

}
int main()
{
    system("chcp 65001 > nul");
    setlocale(LC_ALL, "RUS");
    cout << "                  АиСД лаба 2\n";
    cout << "\n";
    cout << "\n";
    cout << "\n";
    //checkBST();
	cout << "\n\n\n";
    cout << "\n";
    cout << "\n";
    cout << "\n";
    checkAVL();
    checkBST();
    return 0;
}