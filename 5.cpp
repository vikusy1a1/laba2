#include <iostream>
#include <fstream>
#include <functional>
#include <string>

using namespace std;


// Определение структуры узла бинарного дерева поиска
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Вспомогательная функция для поиска минимального значения в дереве
TreeNode* findMin(TreeNode* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

// Функция для удаления узла с заданным значением из бинарного дерева поиска
TreeNode* deleteNode(TreeNode* root, int key) {
    if (root == nullptr) {
        return root; // Базовый случай: дерево пустое или узел не найден
    }

    if (key < root->val) {
        root->left = deleteNode(root->left, key); // Идем в левое поддерево
    }
    else if (key > root->val) {
        root->right = deleteNode(root->right, key); // Идем в правое поддерево
    }
    else {
        // Узел найден: нужно удалить его
        if (root->left == nullptr) {
            // Узел не имеет левого ребенка
            TreeNode* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            // Узел не имеет правого ребенка
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }

        // Узел имеет двух детей
        TreeNode* temp = findMin(root->right); // Находим минимальное значение в правом поддереве
        root->val = temp->val; // Копируем значение минимального узла
        root->right = deleteNode(root->right, temp->val); // Удаляем минимальный узел в правом поддереве
    }
    return root;
}

// Вспомогательная функция для вставки нового узла в бинарное дерево поиска
TreeNode* insertNode(TreeNode* root, int key) {
    if (root == nullptr) {
        return new TreeNode(key);
    }

    if (key < root->val) {
        root->left = insertNode(root->left, key);
    }
    else if (key > root->val) {
        root->right = insertNode(root->right, key);
    }

    return root;
}

// Вспомогательная функция для вывода дерева (in-order traversal)
void inorderTraversal(TreeNode* root) {
    if (root != nullptr) {
        inorderTraversal(root->left);
        cout << root->val << " ";  // также выводим в консоль
        inorderTraversal(root->right);
    }
}

int main() {
    TreeNode* root = nullptr;

    // Вставка узлов в дерево
    root = insertNode(root, 22);
    root = insertNode(root, 12);
    root = insertNode(root, 30);
    root = insertNode(root, 17);
    root = insertNode(root, 13);
    root = insertNode(root, 18);
    root = insertNode(root, 8);
    root = insertNode(root, 4);
    root = insertNode(root, 9);
    

    cout << "In-order traversal before deletion: ";
    inorderTraversal(root);
    cout << endl;

    int key = 12;
    root = deleteNode(root, key);

    cout << "In-order traversal after deletion: ";
    inorderTraversal(root);
    cout << endl;

    return 0;
}
