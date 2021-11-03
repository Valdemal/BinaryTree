//Конструктор бинарного дерева
template <typename baseType>
BinaryTree<baseType>::BinaryTree(){
    root = nullptr;
}

// Возвращает ИСТИНА, если узел дерева, который хранит данные key, есть
// в дереве, иначе ЛОЖЬ
template <typename baseType>
bool BinaryTree<baseType>::find(baseType key) {
    nodePtr current = root;
    while (current->data() != key) {
        if (key < current->data())
            current = current->leftChild;
        else
            current = current->rightChild;

        if (current == nullptr)
            return false;
    }
    return true;
}

// Добавляет key в бинарное дерево
template <typename baseType>
void BinaryTree<baseType>::insert(baseType key) {
    auto *newNode = new TreeNode<baseType>(key); // Создание узла
    if (root == nullptr) // Дерево путое
        root = newNode;
    else { // Дерево не пустое
        nodePtr current = root, parent;
        while (current) { // Пока текущий узел существует
            parent = current;
            if (key < current->data()) {
                current = current->leftChild;
                if (current == nullptr) {
                    parent->leftChild = newNode;
                }
            } else {
                current = current->rightChild;
                if (current == nullptr) {
                    parent->rightChild = newNode;
                }
            }
        }
    }
}

/* Удаляет из дерева узел, который хранит данные key, возвращает значение
* ИСТИНА, если данные успешно удалены, возвращает ЛОЖЬ,
* если удаляемый узел не найден */
template <typename baseType>
bool BinaryTree<baseType>::remove(baseType key) {
    if (root == nullptr)
        return false;

    nodePtr current = root, parent = root;
    bool isLeftChild = true;

    while (current->data() != key) {//Поиск узла
        parent = current;
        if (key < current->data()) {
            isLeftChild = true;
            current = current->leftChild;
        } else {
            isLeftChild = false;
            current = current->rightChild;
        }
        if (current == nullptr)
            return false;
    }

    // Удаляемый узел не имеет потомков
    if (current->leftChild == nullptr && current->rightChild == nullptr) {
        if (current == root) {
            root = nullptr;
        } else if (isLeftChild) {
            parent->leftChild = nullptr;
        } else {
            parent->rightChild = nullptr;
        }

    } else if (current->rightChild == nullptr) { // Имеет левого потомка
        if (current == root) {
            root = current->leftChild;
        } else if (isLeftChild) {
            parent->leftChild = current->leftChild;
        } else {
            parent->rightChild = current->leftChild;
        }
    } else if (current->leftChild == nullptr) { // Имеет правого потомка
        if (current == root) {
            root = current->rightChild;
        } else if (isLeftChild) {
            parent->leftChild = current->rightChild;
        } else {
            parent->rightChild = current->rightChild;
        }
    } else { // Имеет двух потомков
        nodePtr successor = getSuccessor(current); // Приемник узла

        if (current == root) {
            root = successor;
        } else if (isLeftChild) {
            parent->leftChild = successor;
        } else {
            parent->rightChild = successor;
        }
        successor->leftChild = current->leftChild;
    }
    delete current; // Освобождение памяти занимаемой узлом
    return true;
}



// Возвращает указатель на узел-приемник узла delNode
template <typename baseType>
TreeNode<baseType> *BinaryTree<baseType>::getSuccessor(nodePtr delNode) {
    nodePtr successorParent = delNode, successor = delNode;
    // Начинаем поиск с правого потомка
    nodePtr current = delNode->rightChild;

    while (current != nullptr) {
        successorParent = successor;
        successor = current;
        current = current->leftChild;
    }

    // Если приемник не правый потомок
    if (successor != delNode->rightChild) {
        //родителю приемника присваиваем указатель на правого потомка приемника
        successorParent->leftChild = successor->rightChild;
        // А правому потомку приемника указатель на правого потомка
        // удаляемого узла
        successor->rightChild = delNode->rightChild;
    }
    return successor;
}

// Возвращает максимальное значение ключа в дереве
template <typename baseType>
baseType BinaryTree<baseType>::max() {
    nodePtr current, last;
    current = root;
    while (current != nullptr) {
        last = current;
        current = current->rightChild;
    }
    return last->data();
}

// Возвращает минимальное значение ключа в дереве
template <typename baseType>
baseType BinaryTree<baseType>::min() {
    nodePtr current, last;
    current = root;
    while (current != nullptr) {
        last = current;
        current = current->leftChild;
    }
    return last->data();
}

// Выполняет симметричный обход дерева, вызывая для каждого узла функцию function
template <typename baseType>
void BinaryTree<baseType>::inOrder(void function(baseType)) {
    _inOrder(root, function);
}

// Выполняет симметричный обход начиная с localRoot, вызывая для каждого
// узла функцию function
template <typename baseType>
void BinaryTree<baseType>::_inOrder(nodePtr localRoot,
                                    void function(baseType)) {
    if (localRoot != nullptr) {
        _inOrder(localRoot->leftChild, function);
        function(localRoot->data());
        _inOrder(localRoot->rightChild, function);
    }
}

// Выполняет прямой обход дерева, вызывая для каждого узла функцию function
template <typename baseType>
void BinaryTree<baseType>::preOrder(void function(baseType)) {
    _preOrder(root, function);
}

// Выполняет прямой обход начиная с localRoot, вызывая для каждого узла
// функцию function
template <typename baseType>
void BinaryTree<baseType>::_preOrder(nodePtr localRoot,
                                   void function(baseType)) {
    if (localRoot != nullptr) {
        function(localRoot->data());
        _preOrder(localRoot->leftChild, function);
        _preOrder(localRoot->rightChild, function);
    }
}

// Выполняет обратный обход дерева, вызывая для каждого узла функцию function
template <typename baseType>
void BinaryTree<baseType>::postOrder(void function(baseType)) {
    _postOrder(root, function);
}

// Выполняет прямой обход начиная с localRoot, вызывая для каждого узла
// функцию function
template <typename baseType>
void BinaryTree<baseType>::_postOrder(nodePtr localRoot,
                                     void function(baseType)) {
    if (localRoot != nullptr) {
        _postOrder(localRoot->leftChild, function);
        _postOrder(localRoot->rightChild, function);
        function(localRoot->data());
    }
}

// Деструктор бинарного дерева
template<typename baseType>
BinaryTree<baseType>::~BinaryTree() {
    deleteTree(root);
    root = nullptr;
}

//Освобождает память, которую занимает поддерево с корнем в узле localRoot
template<typename baseType>
void BinaryTree<baseType>::deleteTree(nodePtr localRoot) {
    if (localRoot != nullptr) {
        deleteTree(localRoot->leftChild);
        deleteTree(localRoot->rightChild);
        delete localRoot;
    }
}