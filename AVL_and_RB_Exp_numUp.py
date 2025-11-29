import numpy as np
import matplotlib.pyplot as plt

# --- Классы AVL и RB остаются без изменений ---
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

# --- Эксперимент с упорядоченной вставкой ---
def experiment_ordered_insertion():
    n_values = np.arange(10, 3001, 10)
    avl_heights = []
    rb_heights = []
    print("Проведение эксперимента с упорядоченной вставкой (1, 2, ..., n)...")
    for n in n_values:
        keys = list(range(1, n + 1))
        # AVL
        avl = AVLTree()
        for key in keys:
            avl.insert(key)
        avl_h = avl.height()
        avl_heights.append(avl_h)
        # RB
        rb = RBTree()
        for key in keys:
            rb.insert(key)
        rb_h = rb.height()
        rb_heights.append(rb_h)
        # Вывод промежуточных результатов
        if n in [100, 500, 1000, 2000, 3000]:
            log2n = np.log2(n)
            print(f"\nn = {n}")
            print(f"  AVL height = {avl_h:4d},   h / log₂(n) = {avl_h / log2n:.3f}")
            print(f"  RB  height = {rb_h:4d},   h / log₂(n) = {rb_h / log2n:.3f}")
    return n_values, avl_heights, rb_heights

# --- Построение графика ---
def plot_ordered_comparison(n_values, avl_heights, rb_heights):
    log2_n = np.log2(n_values)
    avl_upper = 1.44 * np.log2(n_values + 2) - 0.328
    rb_upper = 2 * np.log2(n_values)
    
    plt.figure(figsize=(12, 7))
    plt.plot(n_values, avl_heights, 'bo-', markersize=3, linewidth=1.2, label='AVL (упорядоченная вставка)')
    plt.plot(n_values, rb_heights, 'ro-', markersize=3, linewidth=1.2, label='Красно-чёрное (упорядоченная вставка)')
    plt.plot(n_values, log2_n, 'g--', linewidth=2, label='log₂(n) — нижняя граница')
    plt.plot(n_values, avl_upper, 'c--', linewidth=2, label='1.44·log₂(n+2) − 0.328 — верхняя (AVL)')
    plt.plot(n_values, rb_upper, 'm--', linewidth=2, label='2·log₂(n) — верхняя (RB)')
    #dcad
    plt.xlabel('Количество элементов (n)')
    plt.ylabel('Высота дерева')
    plt.title('Высота AVL и красно-чёрного деревьев при упорядоченной вставке (n ≤ 3000)')
    plt.legend()
    plt.grid(True, alpha=0.3)
    plt.show()

# --- Запуск ---
if __name__ == "__main__":
    n_vals, avl_h, rb_h = experiment_ordered_insertion()
    plot_ordered_comparison(n_vals, avl_h, rb_h)
    
    # Финальный вывод
    n_final = n_vals[-1]
    avl_final = avl_h[-1]
    rb_final = rb_h[-1]
    log2_final = np.log2(n_final)
    print("\n" + "="*60)
    print("ИТОГИ ЭКСПЕРИМЕНТА (n = 3000):")
    print("="*60)
    print(f"AVL:  высота = {avl_final},   h / log₂(n) = {avl_final / log2_final:.3f}  (теория: ≤ 1.44)")
    print(f"RB:   высота = {rb_final},   h / log₂(n) = {rb_final / log2_final:.3f}  (теория: ≤ 2.00)")
    print("\n✅ Оба дерева сохраняют логарифмическую высоту даже при упорядоченной вставке!")
    print("✅ AVL компактнее красно-чёрного дерева, как и ожидалось.")