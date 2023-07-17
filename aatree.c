#include <stdio.h>
#include <stdlib.h>
//to find prev and next element

// Структура для представления узла AA-дерева
struct Node {
    int key;
    int level;
    struct Node *left;
    struct Node *right;
};

// Создание нового узла дерева
struct Node *newNode(int key) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->key = key;
    node->level = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Функция для правого поворота узла
struct Node *skew(struct Node *node) {
    if (node == NULL)
        return NULL;
    else if (node->left == NULL)
        return node;
    else if (node->left->level == node->level) {
        struct Node *leftChild = node->left;
        node->left = leftChild->right;
        leftChild->right = node;
        return leftChild;
    }
    return node;
}

// Функция для выполнения split-операции на узле
struct Node *split(struct Node *node) {
    if (node == NULL)
        return NULL;
    else if (node->right == NULL || node->right->right == NULL)
        return node;
    else if (node->level == node->right->right->level) {
        struct Node *rightChild = node->right;
        node->right = rightChild->left;
        rightChild->left = node;
        rightChild->level = rightChild->level + 1;
        return rightChild;
    }
    return node;
}

// Функция для вставки ключа в AA-дерево
struct Node *insert(struct Node *node, int key) {
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Дублирующиеся ключи не допускаются в AA-дереве
        return node;

    node = skew(node);
    node = split(node);
    return node;
}

// Функция для поиска минимального ключа в дереве
struct Node *findMin(struct Node *node) {
    if (node == NULL)
        return NULL;
    else if (node->left == NULL)
        return node;
    else
        return findMin(node->left);
}

// Функция для поиска максимального ключа в дереве
struct Node *findMax(struct Node *node) {
    if (node == NULL)
        return NULL;
    else if (node->right == NULL)
        return node;
    else
        return findMax(node->right);
}

// Функция для поиска следующего ключа в дереве
struct Node *findNext(struct Node *node, int key) {
    if (node == NULL)
        return NULL;
    if (key < node->key) {
        struct Node *next = findNext(node->left, key);
        if (next == NULL)
            return node;
        return next;
    }
    return findNext(node->right, key);
}

// Функция для поиска предыдущего ключа в дереве
struct Node *findPrev(struct Node *node, int key) {
    if (node == NULL)
        return NULL;
    if (key > node->key) {
        struct Node *prev = findPrev(node->right, key);
        if (prev == NULL)
            return node;
        return prev;
    }
    return findPrev(node->left, key);
}

// Пример использования
int main() {
    struct Node *root = NULL;

    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 10);
    root = insert(root, 25);
    root = insert(root, 35);
    root = insert(root, 50);

    int key = 25;
    struct Node *next = findNext(root, key);
    struct Node *prev = findPrev(root, key);

    printf("Key: %d\n", key);
    if (next != NULL)
        printf("Next key: %d\n", next->key);
    else
        printf("Next key not found\n");
    if (prev != NULL)
        printf("Prev key: %d\n", prev->key);
    else
        printf("Prev key not found\n");

    return 0;
}
