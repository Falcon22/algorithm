#include <iostream>

int joseph(int n, int k) {
    int j = 1;
    for (int i = 2; i <= n; i++) {
        j = (j + k - 1) % i + 1;
    }
    return j;
}

int main(int argc, const char * argv[]) {
    int n, k;
    std::cin >> n >> k;
    std::cout << joseph(n, k) << std::endl;
    return 0;
}