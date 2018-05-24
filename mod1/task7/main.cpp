#include <iostream>
#include <cstring>

int bitsword = 63;

short digit(uint64_t x, int n) {
    for (int i = 0; i < n; i++) {
        x = x >> 1;
    }
    return x & 1;
}

void binaryQuickSort(uint64_t* arr, long l, long r, int d) {
    long i = l, j = r;
    if (r <= l || d < 0) {
        return;
    }
    while (j != i) {
        while (digit(arr[i], d) == 0 && i < j) {
            i++;
        }
        while (digit(arr[j], d) == 1 && j > i) {
            j--;
        }
        std::swap(arr[i], arr[j]);
    }
    if (digit(arr[r], d) == 0) {
        j++;
    }
    binaryQuickSort(arr, l, j - 1, d - 1);
    binaryQuickSort(arr, j, r, d - 1);
}

int main(int argc, const char * argv[]) {
    long n = 0;
    std::cin >> n;
    uint64_t* arr = new uint64_t[n];

    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    binaryQuickSort(arr, 0, n - 1, bitsword);
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    delete[] arr;
    return 0;
}