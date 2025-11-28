
#include"BST.h"
#include <iostream>
using namespace std;


class AVl{};

int main()
{
    system("chcp 65001 > nul");
    setlocale(LC_ALL, "RUS");
    cout << "                  Алг лаба 2\n";
    cout << "\n";
    cout << "\n";
    cout << "\n";

    int count;
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
    return 0;
}