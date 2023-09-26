#include <iostream>
#include <omp.h>

int main() {
    const int size = 12;
    int a[size];
    int b[size];
    int c[size];

    const int threads_in_first_region = 3;
    const int threads_in_second_region = 4;

#pragma omp parallel num_threads(threads_in_first_region)
    {
        int thread_id = omp_get_thread_num();
        int total_threads = omp_get_num_threads();

        int chunk_size = size / total_threads;
        int start = thread_id * chunk_size;
        int end = (thread_id == total_threads - 1) ? size : start + chunk_size;

        for (int i = start; i < end; i++) {
            a[i] = i * 2;
            b[i] = i * 3;
        }

        std::cout << "Parallel Region 1: Thread ID = " << thread_id << ", Total Threads = " << total_threads << std::endl;
    }

#pragma omp parallel num_threads(threads_in_second_region)
    {
        int thread_id = omp_get_thread_num();
        int total_threads = omp_get_num_threads();

        int chunk_size = size / total_threads;

#pragma omp for schedule(dynamic, chunk_size)
        for (int i = 0; i < size; i++) {
            c[i] = a[i] + b[i];
        }

        std::cout << "Parallel Region 2: Thread ID = " << thread_id << ", Total Threads = " << total_threads << std::endl;
    }

    // Вывод элементов массивов a, b и c
    std::cout << "Array a: ";
    for (int i = 0; i < size; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Array b: ";
    for (int i = 0; i < size; i++) {
        std::cout << b[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Array c: ";
    for (int i = 0; i < size; i++) {
        std::cout << c[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
