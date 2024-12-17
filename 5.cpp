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
    int value;

    // Ввод значений от пользователя
    cout << "Enter the values to insert into the tree (enter -1 to complete the input):\n";
    while (true) {
        cin >> value;
        if (value == -1) {
            break;
        }
        root = insertNode(root, value);
    }

    cout << "In-order traversal before deletion: ";
    inorderTraversal(root);
    cout << endl;

    cout << "Enter the node you want to delete: ";
    cin >> value; // считываем значение для удаления
    root = deleteNode(root, value); // удаляем узел

    cout << "In-order traversal after deletion: ";
    inorderTraversal(root);
    cout << endl;

    return 0;
}
