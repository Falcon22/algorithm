#include <iostream>
#include <queue>

template <typename T>
struct BinTreeNode {
public:
    BinTreeNode() : _data(0), _left(nullptr), _right(nullptr), _parent(nullptr) {};
    BinTreeNode(T data) : _data(data), _left(nullptr), _right(nullptr), _parent(nullptr) {};
    BinTreeNode(BinTreeNode* parent, T data): _data(data), _left(nullptr), _right(nullptr), _parent(parent) {};
    BinTreeNode(BinTreeNode* parent, BinTreeNode* left, BinTreeNode* right, T data): _data(data), _left(left), _right(right), _parent(parent) {};

    T _data;
    BinTreeNode* _left;
    BinTreeNode* _right;
    BinTreeNode* _parent;
};

template <typename T>
class BinTree {
public:
    BinTree(): _root(nullptr), _size(0) {};
    BinTree(BinTreeNode<T>* root): _root(root), _size(1) {};
    ~BinTree();

    void insert(const T key);
    void traversBFS();

    const long int height(BinTreeNode<T> *p);
    const long int getWidth(BinTreeNode<T>* root, long int level);
    const long int getMaxWidth();

private:
    BinTreeNode<T>* _root;
    BinTreeNode<T>* _size;
};

template <typename T>
BinTree<T>::~BinTree<T>() {
    if (_root != nullptr) {
        std::queue<BinTreeNode<T>*> q;
        q.push(_root);
        while (!q.empty()) {
            BinTreeNode<T>* node = q.front();
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
}

template <typename T>
void BinTree<T>::insert(T key) {
    if (_root == nullptr) {
        _root = new BinTreeNode<T>(key);
        return;
    }

    BinTreeNode<T>* now = _root;
    bool find = false;
    while (!find) {
        if (now->_data > key) {
            if (now->_left != nullptr) {
                now = now->_left;
            } else {
                now->_left = new BinTreeNode<T>(key);
                find = true;
            }
        } else {
            if (now->_right != nullptr) {
                now = now->_right;
            } else {
                now->_right = new BinTreeNode<T>(key);
                find = true;
            }
        }
    }
    _size++;
}

template <typename T>
void BinTree<T>::traversBFS() {
    if (_root == nullptr) {
        return;
    }

    std::queue<BinTreeNode<T>*> q;
    q.push(_root);
    while (!q.empty()) {
        BinTreeNode<T>* node = q.front();
        q.pop();
        if (node->_left != nullptr) {
            q.push(node->_left);
        }
        if (node->_right != nullptr) {
            q.push(node->_right);
        }
        std::cout << node->_data << std::endl;
    }
}

template <typename T>
const long int BinTree<T>::height(BinTreeNode<T>* p) {
    long int h1 = 0, h2 = 0;
    if (p == nullptr) {
        return 0;
    }
    if (p->_left != nullptr) {
        h1 = height(p->_left);
    }
    if (p->_right != nullptr) {
        h2 = height(p->_right);
    }
    return std::max(h1, h2) + 1;
}

template <typename T>
const long int BinTree<T>::getWidth(BinTreeNode<T>* root, long int level) {
    if (root == nullptr) {
        return 0;
    }
    if (level == 1) {
        return 1;
    } else if (level > 1) {
        return getWidth(root->_left, level - 1) + getWidth(root->_right, level - 1);
    }
    return getWidth(root->_right, level - 1);
}

template <typename T>
const long int BinTree<T>::getMaxWidth() {
    long int maxWidth = 0, width = 0;
    long int h = height(_root);
    for (long int i = 1; i < h; i++) {
        width = getWidth(_root, i);
        if (width > maxWidth) {
            maxWidth = width;
        }
    }
    return maxWidth;
}

template <typename T>
struct TreapNode {
public:
    TreapNode() : _key(0), _priority(0), _left(nullptr), _right(nullptr) {};
    TreapNode(T x, long long int y) : _key(x), _priority(y), _left(nullptr), _right(nullptr) {};

    T _key;
    long long int _priority;

    TreapNode* _left;
    TreapNode* _right;
};

template <typename T>
class Treap {
public:
    Treap() : _root(nullptr), _size(0) {};
    Treap(TreapNode<T>* root): _root(root), _size(1) {};
    ~Treap();

    void add(T x, long long int priority);
    void insert(TreapNode<T>*& root, TreapNode<T>* vertex);
    void traversBFS();

    const long int height(TreapNode<T>* p);
    const long int getWidth(TreapNode<T>* root, long int level);
    const long int getMaxWidth();

private:
    void split(TreapNode<T>* currentNode, long long int key, TreapNode<T>*& left, TreapNode<T>*& right);

    TreapNode<T>* _root;
    long int _size;
};

template <typename T>
Treap<T>::~Treap<T>() {
    if (_root != nullptr) {
        std::queue<TreapNode<T>*> q;
        q.push(_root);
        while (!q.empty()) {
            TreapNode<T>* node = q.front();
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
}

template <typename T>
void Treap<T>::split(TreapNode<T>* currentNode, long long int key, TreapNode<T>*& left, TreapNode<T>*& right) {
    if (currentNode == nullptr) {
        left = right = nullptr;
        return;
    }
    if (currentNode->_key <= key) {
        split(currentNode->_right, key, currentNode->_right, right);
        left = currentNode;
    } else {
        split(currentNode->_left, key, left, currentNode->_left);
        right = currentNode;
    }
}

template <typename T>
void Treap<T>::add(T x, long long int priority) {
    TreapNode<T>* newNode = new TreapNode<T>(x, priority);
    insert(_root, newNode);
}

template <typename T>
void Treap<T>::insert(TreapNode<T>*& root, TreapNode<T>* vertex) {
    if (root == nullptr) {
        root = vertex;
        return;
    }
    if (root->_priority > vertex->_priority) {
        if (vertex->_key < root->_key) {
            insert(root->_left, vertex);
        } else {
            insert(root->_right, vertex);
        }
        return;
    }
    split(root, vertex->_key, vertex->_left, vertex->_right);
    root = vertex;
}

template <typename T>
void Treap<T>::traversBFS() {
    if (_root == nullptr) {
        return;
    }

    std::queue<TreapNode<T>*> q;
    q.push(_root);
    while (!q.empty()) {
        TreapNode<T>* node = q.front();
        q.pop();
        if (node->_left != nullptr) {
            q.push(node->_left);
        }
        if (node->_right != nullptr) {
            q.push(node->_right);
        }
        std::cout << node->_key << " " << node->_priority << std::endl;
    }
}

template <typename T>
const long int Treap<T>::height(TreapNode<T>* p) {
    long int h1 = 0, h2 = 0;
    if (p == nullptr) {
        return 0;
    }
    if (p->_left != nullptr) {
        h1 = height(p->_left);
    }
    if (p->_right != nullptr) {
        h2 = height(p->_right);
    }
    return std::max(h1, h2) + 1;
}

template <typename T>
const long int Treap<T>::getWidth(TreapNode<T>* root, long int level) {
    if (root == nullptr) {
        return 0;
    }
    if (level == 1) {
        return 1;
    } else if (level > 1) {
        return getWidth(root->_left, level - 1) + getWidth(root->_right, level - 1);
    }
    return getWidth(root->_right, level - 1);
}

template <typename T>
const long int Treap<T>::getMaxWidth() {
    long int maxWidth = 0, width = 0;
    long int h = height(_root);
    for (long int i = 1; i < h; i++) {
        width = getWidth(_root, i);
        if (width > maxWidth) {
            maxWidth = width;
        }
    }
    return maxWidth;
}

int main(int argc, const char * argv[]) {
    Treap<long int> treap;
    BinTree<long int> tree;
    long int n = 0, x = 0, p = 0;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> x >> p;
        treap.add(x, p);
        tree.insert(x);
    }
    std::cout << treap.getMaxWidth() - tree.getMaxWidth() << std::endl;
    return 0;
}