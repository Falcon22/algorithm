#include <iostream>
#include <queue>
#include <stack>

template <typename T>
class AVLTreeNode {
public:
    AVLTreeNode(T x) : _data(x), _left(nullptr), _right(nullptr), _count(1), _height(1) {};

    T _data;
    AVLTreeNode<T>* _left;
    AVLTreeNode<T>* _right;

    int _count;
    int _height;
};

template <typename T>
class AVLTree {
public:
    AVLTree() : _root(nullptr), _size(0) {};
    AVLTree(AVLTreeNode<T>* root, int size) : _root(root), _size(size) {};
    ~AVLTree();

    int insert(const T data);
    void remove(int index);

private:
    const int height(AVLTreeNode<T>* node);
    const int count(AVLTreeNode<T>* node);
    const int bfactor(AVLTreeNode<T>* node);

    void fixHeight(AVLTreeNode<T>* node);
    void fixCount(AVLTreeNode<T>* node);

    AVLTreeNode<T>* rotateRight(AVLTreeNode<T>* node);
    AVLTreeNode<T>* rotateLeft(AVLTreeNode<T>* node);
    AVLTreeNode<T>* balance(AVLTreeNode<T>* node);

    AVLTreeNode<T>* removeMin(AVLTreeNode<T>* node, AVLTreeNode<T>* root);
    AVLTreeNode<T>* removeNode(AVLTreeNode<T>* node, int ind);

    AVLTreeNode<T>* _root;
    int _size;
};

template <typename T>
AVLTree<T>::~AVLTree() {
    std::queue<AVLTreeNode<T>*> q;
    if (_root != nullptr) {
        q.push(_root);
    }

    while (!q.empty()) {
        AVLTreeNode<T>* node = q.front();
        q.pop();
        if (node->_left != nullptr) {
            q.push(node->_left);
        }
        if (node->_right != nullptr) {
            q.push(node->_right);
        }
        delete node;
    }
}

template <typename T>
const int AVLTree<T>::height(AVLTreeNode<T>* node) {
    return node != nullptr ? node->_height : 0;
}

template <typename T>
const int AVLTree<T>::count(AVLTreeNode<T>* node) {
    return node != nullptr ? node->_count : 0;
}

template <typename T>
const int AVLTree<T>::bfactor(AVLTreeNode<T>* node) {
    return height(node->_right) - height(node->_left);
}

template <typename T>
void AVLTree<T>::fixHeight(AVLTreeNode<T>* node) {
    int hl = height(node->_left);
    int hr = height(node->_right);
    node->_height = (hl > hr ? hl : hr) + 1;
}

template <typename T>
void AVLTree<T>::fixCount(AVLTreeNode<T> *node) {
    int cl = count(node->_left);
    int cr = count(node->_right);
    node->_count = cl + cr + 1;
}

template <typename T>
AVLTreeNode<T>* AVLTree<T>::rotateRight(AVLTreeNode<T>* p) {
    AVLTreeNode<T>* q = p->_left;
    p->_left = q->_right;
    q->_right = p;
    fixHeight(p);
    fixHeight(q);
    fixCount(p);
    fixCount(q);
    return q;
}

template <typename T>
AVLTreeNode<T>* AVLTree<T>::rotateLeft(AVLTreeNode<T>* q) {
    AVLTreeNode<T>* p = q->_right;
    q->_right = p->_left;
    p->_left = q;
    fixHeight(q);
    fixHeight(p);
    fixCount(q);
    fixCount(p);
    return p;
}

template <typename T>
AVLTreeNode<T>* AVLTree<T>::balance(AVLTreeNode<T>* node) {
    fixHeight(node);
    if (bfactor(node) == 2) {
        if (bfactor(node->_right) < 0) {
            node->_right = rotateRight(node->_right);
        }
        return rotateLeft(node);
    }

    if (bfactor(node) == -2) {
        if (bfactor(node->_left) > 0) {
            node->_left = rotateLeft(node->_left);
        }
        return rotateRight(node);
    }
    fixHeight(node);
    fixCount(node);
    return node;
}


template <typename T>
int AVLTree<T>::insert(const T data) {
    if (_size == 0) {
        _root = new AVLTreeNode<T>(data);
        _size++;
        return 0;
    }
    int ind = 0;
    AVLTreeNode<T>* node = _root;
    std::stack<std::pair<AVLTreeNode<T>*, bool>> s;
    bool find = false;
    std::pair<AVLTreeNode<T>*, bool> tmp;

    while (!find) {
        if (data > node->_data) {
            if (node->_left != nullptr) {
                tmp.first = node;
                tmp.second = true;
                s.push(tmp);
                node = node->_left;
            } else {
                node->_left = new AVLTreeNode<T>(data);
                find = true;
            }
        } else {
            ind += count(node->_left) + 1;
            if (node->_right != nullptr) {
                tmp.first = node;
                tmp.second = false;
                s.push(tmp);
                node = node->_right;
            } else {
                node->_right = new AVLTreeNode<T>(data);
                find = true;
            }
        }
    }
    _size++;

    while (!s.empty()) {
        if (s.top().second) {
            s.top().first->_left = balance(s.top().first->_left);
        } else {
            s.top().first->_right = balance(s.top().first->_right);
        }
        s.pop();
    }
    _root = balance(_root);
    return ind;
}

template <typename T>
AVLTreeNode<T>* AVLTree<T>::removeMin(AVLTreeNode<T>* node, AVLTreeNode<T>* root) {
    if (node->_left == nullptr) {
        root->_data = node->_data;
        AVLTreeNode<T>* tmp = node->_right;
        delete node;
        return tmp;
    }
    node->_left = removeMin(node->_left, root);
    return balance(node);
}

template <typename T>
AVLTreeNode<T>* AVLTree<T>::removeNode(AVLTreeNode<T> *node, int ind) {
    if (node == nullptr) {
        return nullptr;
    }

    if (node->_left == nullptr && node->_right == nullptr) {
        delete node;
        return nullptr;
    }

    if (count(node->_left) > ind) {
        node->_left = removeNode(node->_left, ind);
    } else if (count(node->_left) < ind) {
        node->_right = removeNode(node->_right, ind - (count(node->_left) + 1));
    } else {
        if (node->_left != nullptr && node->_right != nullptr) {
            node->_right = removeMin(node->_right, node);
        } else if (node->_left != nullptr) {
            AVLTreeNode<T>* tmp = node->_left;
            delete node;
            node = tmp;
        } else {
            AVLTreeNode<T>* tmp = node->_right;
            delete node;
            node = tmp;
        }
    }
    if (node != nullptr) {
        return balance(node);
    }
    return nullptr;
}

template <typename T>
void AVLTree<T>::remove(int index) {
    _root = removeNode(_root, index);
    _size--;
}

int main(int argc, const char * argv[]) {
    AVLTree<long int> t;
    int n, k, x;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> k >> x;
        if (k == 1) {
            std::cout << t.insert(x) << std::endl;
        } else {
            t.remove(x);
        }
    }
    return 0;
}