#include <iostream>
#include <vector>
#include <ctime>
#include <omp.h>

std::vector<std::vector<double>> GenerateMatrix(int rows, int cols) {
    std::vector<std::vector<double>> matrix(rows, std::vector<double>(cols));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = static_cast<double>(rand()) / RAND_MAX;
        }
    }
    return matrix;
}

std::vector<double> GenerateVector(int size) {
    std::vector<double> vector(size);
    for (int i = 0; i < size; i++) {
        vector[i] = static_cast<double>(rand()) / RAND_MAX;
    }
    return vector;
}

std::vector<double> MatrixVectorMultSeq(const std::vector<std::vector<double>>& matrix, const std::vector<double>& vector) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    int size = vector.size();

    std::vector<double> result(rows, 0.0);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }

    return result;
}

std::vector<double> MatrixVectorMultParallel(const std::vector<std::vector<double>>& matrix, const std::vector<double>& vector) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    std::vector<double> result(rows, 0.0);

#pragma omp parallel for
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
#pragma omp atomic
            result[i] += matrix[i][j] * vector[j];
        }
    }

    return result;
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    const int matrix_rows = 10000;
    const int matrix_cols = 10000;
    const int vector_size = 10000;

    std::vector<std::vector<double>> matrix = GenerateMatrix(matrix_rows, matrix_cols);
    std::vector<double> vector = GenerateVector(vector_size);

    double start_time_seq = omp_get_wtime();
    std::vector<double> result_seq = MatrixVectorMultSeq(matrix, vector);
    double end_time_seq = omp_get_wtime();
    double seq_time = end_time_seq - start_time_seq;

    double start_time_parallel = omp_get_wtime();
    std::vector<double> result_parallel = MatrixVectorMultParallel(matrix, vector);
    double end_time_parallel = omp_get_wtime();
    double parallel_time = end_time_parallel - start_time_parallel;

    std::cout << "Sequential Time: " << seq_time << " seconds" << std::endl;
    std::cout << "Parallel Time: " << parallel_time << " seconds" << std::endl;
    std::cout << "Speedup: " << seq_time / parallel_time << std::endl;

    return 0;
}
