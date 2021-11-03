#ifndef BINARY_TREES_TREE_H
#define BINARY_TREES_TREE_H
#include <iostream>

using namespace std;

template<typename baseType>
class TreeNode { //Узел дерева
private:
    //Тип - указатель на узел дерева с базовым типом типом baseType
    typedef TreeNode<baseType> *nodePtr;

    baseType _data; //Данные, которые хранит узел
public:
    nodePtr leftChild; // Указатель на левого потомка
    nodePtr rightChild; // Указатель на правого потомка

    //Создает узел дерева, который хранит _data
    explicit TreeNode(baseType data) {
        this->_data = data;
        leftChild = rightChild = nullptr;
    }

    //Возвращает данные, которые хранит узел дерева
    inline baseType data(){
        return _data;
    }

}; // конец класс TreeNode

template<typename baseType>
class BinaryTree { // Бинарное дерево поиска
private:
    //Тип - указатель на узел дерева с базовым типом типом baseType
    typedef TreeNode<baseType> *nodePtr;

    nodePtr root; // Корень дерева

public:
    //Конструктор бинарного дерева
    BinaryTree();

    // Деструктор бинарного дерева
    ~BinaryTree();

    // Возвращает ИСТИНА, если узел дерева, который хранит данные key, есть
    // в дереве, иначе ЛОЖЬ
    bool find(baseType key);

    // Добавляет key в бинарное дерево
    void insert(baseType key);

    /* Удаляет из дерева узел, который хранит данные key, возвращает значение
     * ИСТИНА, если данные успешно удалены, возвращает ЛОЖЬ,
     * если удаляемый узел не найден */
    bool remove(baseType key);

    // Возвращает максимальное значение ключа в дереве
    baseType max();

    // Возвращает минимальное значение ключа в дереве
    baseType min();

    // Выполняет симметричный обход дерева, вызывая для каждого узла функцию function
    void inOrder(void function(baseType));

    // Выполняет прямой обход дерева, вызывая для каждого узла функцию function
    void preOrder(void function(baseType));

    // Выполняет обратный обход дерева, вызывая для каждого узла функцию function
    void postOrder(void function(baseType));
private:
    // Возвращает указатель на узел-приемник узла delNode
    nodePtr getSuccessor(nodePtr delNode);

    // Выполняет симметричный обход начиная с localRoot, вызывая для каждого
    // узла функцию function
    void _inOrder(nodePtr localRoot, void function(baseType));

    // Выполняет прямой обход начиная с localRoot, вызывая для каждого узла
    // функцию function
    void _preOrder(nodePtr localRoot, void function(baseType));

    // Выполняет обратный обход начиная с localRoot, вызывая для каждого узла
    // функцию function
    void _postOrder(nodePtr localRoot, void function(baseType));

    //Освобождает память, которую занимает поддерево с корнем в узле localRoot
    void deleteTree(nodePtr localRoot);
};// Конец класса BinaryTree

#include "Tree.tpp"

#endif //BINARY_TREES_TREE_H
