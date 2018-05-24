#include <iostream>

template <typename T>
bool compare(T a, T b)
{
    return a > b;
}

template <typename T, typename Compare>
long int med (T* arr, long int a, long int b, long int c, Compare cmp)
{
    if (cmp(arr[a], arr[b])) {
        if (cmp(arr[c], arr[a])) {
            return a;
        }
        else {
            return cmp(arr[b], arr[c]) ? b : c;
        }
    }

    if (cmp(arr[c], arr[b])) {
        return b;
    }
    else {
        return cmp(arr[a], arr[c]) ? a : c;
    }
}

template <typename T, typename Compare>
long int partition(T* arr, long left, long right, Compare cmp) {
    long int mid;

    if (left != right) {
        mid = med(arr, left, right, left + (right - left) / 2, cmp);
    }
    else {
        mid = left;
    }
    long int i = right, j = right;
    std::swap(arr[mid], arr[left]);

    while (j >= left) {
        if (!cmp(arr[j], arr[left])) {
            j--;
        }
        else {
            std::swap(arr[i], arr[j]);
            i--;
            j--;
        }
    }
    std::swap(arr[left], arr[i]);
    return i;
}

template<typename T, typename Compare>
long findOrderStatistic(T* arr, long left, long right, T k, Compare cmp) {
    while (true) {
        long int mid = partition(arr, left, right, cmp);

        if (mid == k) {
            return arr[mid];
        }
        else if (k < mid) {
            right = mid;
        }
        else {
            left = mid + 1;
        }
    }
}

int main(int argc, const char * argv[]) {
    int n, k;
    std::cin >> n >> k;
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    std::cout << findOrderStatistic(arr, 0, n - 1, k, compare<int>);
    return 0;
}