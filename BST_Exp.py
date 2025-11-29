import numpy as np
import matplotlib.pyplot as plt
import random
from typing import List

class BSTNode:
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None

class BST:
    def __init__(self):
        self.root = None
    
    def insert(self, key):
        if self.root is None:
            self.root = BSTNode(key)
        else:
            self._insert(self.root, key)
    
    def _insert(self, node, key):
        if key < node.key:
            if node.left is None:
                node.left = BSTNode(key)
            else:
                self._insert(node.left, key)
        elif key > node.key:
            if node.right is None:
                node.right = BSTNode(key)
            else:
                self._insert(node.right, key)
    
    def height(self):
        return self._height(self.root)
    
    def _height(self, node):
        if node is None:
            return 0
        return 1 + max(self._height(node.left), self._height(node.right))

def experiment_bst_height():
    n_values = np.arange(10, 3001, 10)
    num_trials = 50
    results = []
    
    print("Проведение эксперимента...")
    
    for n in n_values:
        heights = []
        for trial in range(num_trials):
            bst = BST()
            keys = random.sample(range(1, 100000), n)
            
            for key in keys:
                bst.insert(key)
            
            heights.append(bst.height())
        
        avg_height = np.mean(heights)
        std_height = np.std(heights)
        results.append((n, avg_height, std_height))
        
        if n % 100 == 0:
            print(f"n = {n}, средняя высота = {avg_height:.2f} ± {std_height:.2f}")
    
    return results

def plot_results(results):
    n_values = [r[0] for r in results]
    avg_heights = [r[1] for r in results]
    std_heights = [r[2] for r in results]
    
    log2_n = np.log2(n_values)
    sqrt_n = np.sqrt(n_values)
    two_log2_n = 2 * log2_n
    
    plt.figure(figsize=(12, 8))
    
    plt.errorbar(n_values, avg_heights, yerr=std_heights, 
                fmt='o-', markersize=3, linewidth=1, capsize=3,
                label='Экспериментальная высота BST', alpha=0.7)
    
    plt.plot(n_values, log2_n, 'r--', linewidth=2, label='log₂(n)')
    plt.plot(n_values, two_log2_n, 'g--', linewidth=2, label='2 * log₂(n)')
    plt.plot(n_values, sqrt_n, 'm--', linewidth=2, label='√n')
    
    plt.xlabel('Количество элементов (n)')
    plt.ylabel('Высота дерева')
    plt.title('Экспериментальная зависимость высоты BST от количества элементов')
    plt.legend()
    plt.grid(True, alpha=0.3)

    plt.show()

def analyze_asymptotics(results):
    n_values = [r[0] for r in results]
    avg_heights = [r[1] for r in results]
    
    log_heights = np.log(avg_heights)
    log_n = np.log(n_values)
    
    A = np.vstack([log_n, np.ones(len(log_n))]).T
    k, b = np.linalg.lstsq(A, log_heights, rcond=None)[0]
    
    print(f"\nАнализ асимптотики:")
    print(f"Коэффициент в логарифмической шкале: k = {k:.4f}")
    print(f"Это соответствует h(n) ~ O(n^{k:.4f})")
    
    if 0.4 <= k <= 0.6:
        print("Наблюдается асимптотика O(√n) - характерно для случайных BST")
    elif k <= 0.2:
        print("Наблюдается асимптотика O(log n) - дерево хорошо сбалансировано")
    else:
        print(f"Промежуточная асимптотика O(n^{k:.4f})")
    
    theoretical_log = 0.5
    experimental_ratio = k / theoretical_log
    
    print(f"Отношение экспериментального коэффициента к теоретическому (0.5): {experimental_ratio:.4f}")

def additional_analysis(results):
    n_values = [r[0] for r in results]
    avg_heights = [r[1] for r in results]
    
    height_to_log = [h / np.log2(n) for h, n in zip(avg_heights, n_values)]
    
    plt.figure(figsize=(12, 6))
    plt.plot(n_values, height_to_log, 'b-', linewidth=2)
    plt.axhline(y=2.0, color='r', linestyle='--', label='(теоретически  ~2.0')
    plt.xlabel('Количество элементов (n)')
    plt.ylabel('h(n) / log₂(n)')
    plt.title('Отношение высоты к log₂(n) - проверка асимптотики')
    plt.legend()
    plt.grid(True, alpha=0.3)
    
    plt.show()
    
    print(f"\nАсимптотические отношения:")
    print(f"h(n)/log₂(n) → {height_to_log[-1]:.4f} (теоретически ~ 2.0 )")

if __name__ == "__main__":
    results = experiment_bst_height()
    
    plot_results(results)
    analyze_asymptotics(results)
    additional_analysis(results)