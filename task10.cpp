#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <ctime>

int main() {
    const int size = 30;
    int a[size];

    srand(static_cast<unsigned int>(time(nullptr)));
    for (int i = 0; i < size; i++) {
        a[i] = rand() % 100;
    }

    int count_multiples_of_9 = 0;

    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        if (a[i] % 9 == 0) {
            #pragma omp atomic
            count_multiples_of_9++;
        }
    }

    std::cout << "Count of elements divisible by 9: " << count_multiples_of_9 << std::endl;

    return 0;
}
