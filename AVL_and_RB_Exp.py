import numpy as np
import matplotlib.pyplot as plt
import random

class AVLNode:
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None
        self.height = 1

class AVLTree:
    def __init__(self):
        self.root = None
    
    def _height(self, node):
        if not node:
            return 0
        return node.height
    
    def _balance(self, node):
        if not node:
            return 0
        return self._height(node.left) - self._height(node.right)
    
    def _update_height(self, node):
        if node:
            node.height = 1 + max(self._height(node.left), self._height(node.right))
    
    def _rotate_right(self, y):
        x = y.left
        T2 = x.right
        x.right = y
        y.left = T2
        self._update_height(y)
        self._update_height(x)
        return x
    
    def _rotate_left(self, x):
        y = x.right
        T2 = y.left
        y.left = x
        x.right = T2
        self._update_height(x)
        self._update_height(y)
        return y
    
    def _insert(self, node, key):
        if not node:
            return AVLNode(key)
        if key < node.key:
            node.left = self._insert(node.left, key)
        elif key > node.key:
            node.right = self._insert(node.right, key)
        else:
            return node
        self._update_height(node)
        balance = self._balance(node)
        if balance > 1 and key < node.left.key:
            return self._rotate_right(node)
        if balance < -1 and key > node.right.key:
            return self._rotate_left(node)
        if balance > 1 and key > node.left.key:
            node.left = self._rotate_left(node.left)
            return self._rotate_right(node)
        if balance < -1 and key < node.right.key:
            node.right = self._rotate_right(node.right)
            return self._rotate_left(node)
        return node
    
    def insert(self, key):
        self.root = self._insert(self.root, key)
    
    def height(self):
        return self._height(self.root)

class RBNode:
    def __init__(self, key, color=1, parent=None, left=None, right=None):
        self.key = key
        self.color = color
        self.parent = parent
        self.left = left
        self.right = right

class RBTree:
    def __init__(self):
        self.nil = RBNode(0, color=0)
        self.root = self.nil
    
    def _height(self, node):
        if node == self.nil:
            return 0
        return 1 + max(self._height(node.left), self._height(node.right))
    
    def height(self):
        return self._height(self.root)
    
    def _left_rotate(self, x):
        y = x.right
        x.right = y.left
        if y.left != self.nil:
            y.left.parent = x
        y.parent = x.parent
        if x.parent == self.nil:
            self.root = y
        elif x == x.parent.left:
            x.parent.left = y
        else:
            x.parent.right = y
        y.left = x
        x.parent = y
    
    def _right_rotate(self, y):
        x = y.left
        y.left = x.right
        if x.right != self.nil:
            x.right.parent = y
        x.parent = y.parent
        if y.parent == self.nil:
            self.root = x
        elif y == y.parent.right:
            y.parent.right = x
        else:
            y.parent.left = x
        x.right = y
        y.parent = x
    
    def _insert_fixup(self, z):
        while z.parent.color == 1:
            if z.parent == z.parent.parent.left:
                y = z.parent.parent.right
                if y.color == 1:
                    z.parent.color = 0
                    y.color = 0
                    z.parent.parent.color = 1
                    z = z.parent.parent
                else:
                    if z == z.parent.right:
                        z = z.parent
                        self._left_rotate(z)
                    z.parent.color = 0
                    z.parent.parent.color = 1
                    self._right_rotate(z.parent.parent)
            else:
                y = z.parent.parent.left
                if y.color == 1:
                    z.parent.color = 0
                    y.color = 0
                    z.parent.parent.color = 1
                    z = z.parent.parent
                else:
                    if z == z.parent.left:
                        z = z.parent
                        self._right_rotate(z)
                    z.parent.color = 0
                    z.parent.parent.color = 1
                    self._left_rotate(z.parent.parent)
            if z == self.root:
                break
        self.root.color = 0
    
    def insert(self, key):
        z = RBNode(key, color=1, parent=self.nil, left=self.nil, right=self.nil)
        y = self.nil
        x = self.root
        while x != self.nil:
            y = x
            if z.key < x.key:
                x = x.left
            elif z.key > x.key:
                x = x.right
            else:
                return
        z.parent = y
        if y == self.nil:
            self.root = z
        elif z.key < y.key:
            y.left = z
        else:
            y.right = z
        self._insert_fixup(z)

def experiment_trees_height():
    n_values = np.arange(10, 1001, 20)
    num_trials = 30
    avl_results = []
    rb_results = []
    for n in n_values:
        avl_heights = []
        rb_heights = []
        for _ in range(num_trials):
            keys = random.sample(range(1, 1000000), n)
            avl = AVLTree()
            for key in keys:
                avl.insert(key)
            avl_heights.append(avl.height())
            rb = RBTree()
            for key in keys:
                rb.insert(key)
            rb_heights.append(rb.height())
        avl_avg = np.mean(avl_heights)
        rb_avg = np.mean(rb_heights)
        avl_results.append((n, avl_avg))
        rb_results.append((n, rb_avg))
    return avl_results, rb_results

def plot_comparison(avl_results, rb_results):
    n_values = [r[0] for r in avl_results]
    avl_heights = [r[1] for r in avl_results]
    rb_heights = [r[1] for r in rb_results]
    log2_n = np.log2(n_values)
    phi_log_n = 1.44 * np.log2(np.array(n_values) + 2) - 0.328
    two_log2_n = 2 * np.log2(n_values)
    plt.figure(figsize=(12, 7))
    plt.plot(n_values, avl_heights, 'bo-', markersize=4, linewidth=1.5, label='AVL дерево')
    plt.plot(n_values, rb_heights, 'ro-', markersize=4, linewidth=1.5, label='Красно-чёрное дерево')
    plt.plot(n_values, log2_n, 'g--', linewidth=2, label='log₂(n)')
    plt.plot(n_values, phi_log_n, 'c--', linewidth=2, label='1.44·log₂(n+2) − 0.328')
    plt.plot(n_values, two_log2_n, 'm--', linewidth=2, label='2·log₂(n)')
    plt.xlabel('Количество элементов (n)')
    plt.ylabel('Высота дерева')
    plt.title('Сравнение высот AVL и красно-чёрного деревьев')
    plt.legend()
    plt.grid(True, alpha=0.3)
    plt.show()

if __name__ == "__main__":
    avl_results, rb_results = experiment_trees_height()
    plot_comparison(avl_results, rb_results)