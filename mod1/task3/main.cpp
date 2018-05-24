#include <iostream>

#define BUFSIZE 16

template <typename T>
class Queue {
public:
    Queue() : bufferSize(BUFSIZE), length(0), head(0), tail(0) {
        arr = new T[bufferSize];
    }

    Queue(const size_t size) : bufferSize(size), length(0), head(0), tail(0) {
        arr = new T[bufferSize];
    }

    ~Queue() {
        delete[] arr;
    }

    void pushBack(const T value);
    const T popFront();

private:
    void resizeBuffer();

    T *arr;
    size_t bufferSize;
    size_t length;
    size_t head;
    size_t tail;
};

template <typename T>
void Queue<T>::pushBack(const T value) {
    if (length == (bufferSize - 1)) {
        resizeBuffer();
    }
    arr[tail] = value;
    tail++;
    length++;
    if (tail == bufferSize) {
        tail = 0;
    }
}

template <typename T>
const T Queue<T>::popFront() {
    if (length == 0) {
        return -1;
    }
    T value = arr[head];
    head++;
    length--;
    if (head == bufferSize) {
        head = 0;
    }
    return value;
}

template <typename T>
void Queue<T>::resizeBuffer() {
    T *nArr = new T[bufferSize * 2];
    int h = head;
    int i = 0;
    while (h != tail) {
        nArr[i] = arr[h];
        i++;
        h++;
        if (h == bufferSize) {
            h = 0;
        }
    }
    head = 0;
    tail = i;
    bufferSize *= 2;
    delete[] arr;
    arr = nArr;
}

bool test(Queue<int>& queue, int a, int b) {
    if (a == 3) {
        queue.pushBack(b);
    }
    else {
        if (a == 2 && queue.popFront() != b) {
            return false;
        }
    }
    return true;
}


int main(int argc, const char * argv[]) {
    int n = 0;
    bool key = true;
    std::cin >> n;
    Queue<int> queue(1);

    int a = 0, b = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> a >> b;
        key = test(queue, a, b);
    }

    key ? std::cout << "YES" << std::endl : std::cout << "NO" << std::endl;
    return 0;
}