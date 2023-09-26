#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <ctime>
#include <limits>

int main() {
    const int rows = 6;
    const int cols = 8;
    int d[rows][cols];

    srand(static_cast<unsigned int>(time(nullptr)));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            d[i][j] = rand() % 100;
        }
    }

    int min_value = std::numeric_limits<int>::max();
    int max_value = std::numeric_limits<int>::min();

    #pragma omp parallel for
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
    #pragma omp critical
            {
                if (d[i][j] < min_value) {
                    min_value = d[i][j];
                }
                if (d[i][j] > max_value) {
                    max_value = d[i][j];
                }
            }
        }
    }

    std::cout << "Minimum Value: " << min_value << std::endl;
    std::cout << "Maximum Value: " << max_value << std::endl;

    return 0;
}
