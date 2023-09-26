#include <iostream>
#include <omp.h>

int main() {
    const int size = 10;
    int a[size] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int b[size] = {10, 6, 8, 7, 6, 5, 4, 3, 2, 1};

    double avg_a = 0.0;
    double avg_b = 0.0;

#pragma omp parallel for reduction(+:avg_a, avg_b)
    for (int i = 0; i < size; i++) {
        avg_a += a[i];
        avg_b += b[i];
    }

    avg_a /= size;
    avg_b /= size;

    std::cout << "Average of array a: " << avg_a << std::endl;
    std::cout << "Average of array b: " << avg_b << std::endl;

    if (avg_a == avg_b) {
        std::cout << "The averages are equal." << std::endl;
    } else {
        std::cout << "The averages are not equal." << std::endl;
    }

    return 0;
}