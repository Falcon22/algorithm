#include <iostream>
#include <queue>
#include <stack>

template <typename T>
class BinNode {
public:
    BinNode() : _right(nullptr), _left(nullptr), _parent(nullptr) {};
    BinNode(T data) : _data(data), _right(nullptr), _left(nullptr), _parent(nullptr) {};
    BinNode(T data, BinNode* parent) : _data(data), _right(nullptr), _left(nullptr), _parent(parent) {};

    T _data;
    BinNode* _right;
    BinNode* _left;
    BinNode* _parent;
};

template <typename T>
class BinTree {
public:
    BinTree(): _root(nullptr), _size(0) {}
    ~BinTree();

    void insert(const T& data);
    void traversPostOrder();
    const T& min();
    const T& max();

private:
    BinNode<T>* _root;
    size_t _size;
};

template <typename T>
BinTree<T>::~BinTree<T>() {
    if (_root != nullptr) {
        std::queue<BinNode<T>*> q;
        q.push(_root);
        while (!q.empty()) {
            BinNode<T>* node = q.front();
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
void BinTree<T>::insert(const T& data) {
    if (_size == 0) {
        _root = new BinNode<T>(data);
    } else {
        BinNode<T>* now = _root;
        bool find = false;
        while (!find) {
            if (data < now->_data) {
                if (now->_left != nullptr) {
                    now = now->_left;
                } else {
                    now->_left = new BinNode<T>(data, now);
                    find = true;
                }
            } else {
                if (now->_right != nullptr) {
                    now = now->_right;
                } else {
                    now->_right = new BinNode<T>(data, now);
                    find = true;
                }
            }
        }
    }
    _size++;
}

template <typename T>
void BinTree<T>::traversPostOrder() {
    if (_root == nullptr) {
        return;
    }

    std::stack<BinNode<T>*> stack;
    BinNode<T>* node = _root;
    BinNode<T>* topNode = nullptr;
    BinNode<T>* lastTopNode = nullptr;
    while (!stack.empty() || node != nullptr)
    {
        if (node != nullptr) {
            stack.push(node);
            node = node->_left;
        } else {
            topNode = stack.top();
            if (topNode->_right != nullptr && lastTopNode != topNode->_right) {
                node = topNode->_right;
            } else {
                stack.pop();
                std::cout << topNode->_data << " ";
                lastTopNode = topNode;
            }
        }
    }
}

template <typename T>
const T& BinTree<T>::min() {
    BinNode<T>* now = _root;
    while (now->_left != nullptr) {
        now = now->_left;
    }
    return now->_data;
}

template <typename T>
const T& BinTree<T>::max() {
    BinNode<T>* now = _root;
    while (now->_right != nullptr) {
        now = now->_right;
    }
    return now->_data;
}

int main(int argc, const char * argv[]) {
    BinTree<long long int> map;
    long long int n;
    long long int x;
    std::cin >> n;
    for (long long int i = 0; i < n; i++) {
        std::cin >> x;
        map.insert(x);
    }
    map.traversPostOrder();
    return 0;
}