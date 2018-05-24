#include <iostream>

int find_near(int b, int* A, int n) {
    int k = 1;
    while ((A[k] < b) && (k * 2 < n)) {
        k *= 2;
    }

    int left = k / 2;
    if (A[k] < b) {
        k = n - 1;
    }
    int right = k;

    while (right - left > 1) {
        k = left + (right - left) / 2;
        if (A[k] > b) {
            right = k;
        }
        else {
            left = k;
        }
    }

    if ((b - A[left]) <= (A[right] - b)) {
        return left;
    }
    else {
        return right;
    }
}

int main(int argc, const char * argv[]) {
    int n, m;
    std::cin >> n;
    int* A = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> A[i];
    }
    std::cin >> m;
    int* B = new int[m];
    for (int i = 0; i < m; i++) {
        std::cin >> B[i];
    }
    for (int i = 0; i < m; i++) {
        std::cout << find_near(B[i], A, n) << " ";
    }
    delete [] A;
    delete [] B;
    return 0;
}