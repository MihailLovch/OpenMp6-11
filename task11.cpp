#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <ctime>
#include <limits>

int main() {
    const int size = 100;
    int arr[size];

    srand(static_cast<unsigned int>(time(nullptr)));
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }

    int max_value = std::numeric_limits<int>::min();

    #pragma omp parallel
    {
        int local_max = std::numeric_limits<int>::min();

        #pragma omp for
        for (int i = 0; i < size; i++) {
            if (arr[i] % 7 == 0 && arr[i] > local_max) {
                local_max = arr[i];
            }
        }

        #pragma omp critical
        {
            if (local_max > max_value) {
                max_value = local_max;
            }
        }
    }

    std::cout << "Maximum value divisible by 7: " << max_value << std::endl;

    return 0;
}
