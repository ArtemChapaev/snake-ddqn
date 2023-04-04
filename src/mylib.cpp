#include "mylib.h"

std::vector<double> matrix_multiply_vector(const std::vector<std::vector<double>>& matrix,
                                           const std::vector<double>& vector) {
    std::vector<double> result(matrix.size(), 0.0);

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < vector.size(); j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }

    return result;
}

std::vector<std::vector<double>> matrix_plus_matrix(const std::vector<std::vector<double>>& matrix1,
                                                    const std::vector<std::vector<double>>& matrix2) {
    std::vector<std::vector<double>> result(matrix1.size(), std::vector<double>(matrix1[0].size()));

    for (int i = 0; i < matrix1.size(); i++) {
        for (int j = 0; j < matrix1[i].size(); j++) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }

    return result;
}

std::vector<std::vector<double>> matrix_multiply_matrix(const std::vector<std::vector<double>>& matrix1,
                                                        const std::vector<std::vector<double>>& matrix2) {
    std::vector<std::vector<double>> result(matrix1.size(), std::vector<double>(matrix2[0].size()));

    for (int i = 0; i < matrix1.size(); i++) {
        for (int j = 0; j < matrix2[0].size(); j++) {
            double sum = 0.0;
            for (int k = 0; k < matrix1[0].size(); k++) {
                sum += matrix1[i][k] * matrix2[k][j];
            }
            result[i][j] = sum;
        }
    }

    return result;
}

std::vector<std::vector<double>> transpose_matrix(const std::vector<std::vector<double>>& matrix) {
    std::vector<std::vector<double>> result(matrix[0].size(), std::vector<double>(matrix.size()));

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            result[j][i] = matrix[i][j];
        }
    }

    return result;
}

std::vector<double> vector_plus_vector(const std::vector<double>& vec1, const std::vector<double>& vec2) {
    std::vector<double> result(vec1.size());

    for (int i = 0; i < vec1.size(); i++) {
        result[i] = vec1[i] + vec2[i];
    }

    return result;
}

std::vector<double> relu(const std::vector<double>& vec) {
    std::vector<double> result(vec.size());

    for (int i = 0; i < vec.size(); i++) {
        result[i] = std::max(0.0, vec[i]);
    }

    return result;
}

std::vector<double> softmax(const std::vector<double>& vec) {
    std::vector<double> result(vec.size());
    double sum = 0.0;

    for (int i = 0; i < vec.size(); i++) {
        sum += std::exp(vec[i]);
    }

    for (int i = 0; i < vec.size(); i++) {
        result[i] = std::exp(vec[i]) / sum;
    }

    return result;
}

std::vector<double> vector_multiply_scalar(double num, const std::vector<double>& vector) {
    int vec_size = vector.size();

    std::vector<double> result(vec_size, 0);

    for (int i = 0; i < vec_size; i++) {
        result[i] = num * vector[i];
    }

    return result;
}

std::vector<double> relu_deriv(const std::vector<double>& vec) {
    std::vector<double> result(vec.size());
    for (int i = 0; i < vec.size(); i++) {
        vec[i] < 0 ? result[i] = 0 : result[i] = 1;
    }
    return result;
}

std::vector<double> multiply_vectors(const std::vector<double>& vec1, const std::vector<double>& vec2) {
    std::vector<double> result(vec1.size());
    for (int i = 0; i < vec1.size(); ++i) {
        result[i] = vec1[i] * vec2[i];
    }
    return result;
}

std::vector<std::vector<double>> calculate_dEdW(const std::vector<double>& output,
                                                const std::vector<double>& dEdt) {
    std::vector<std::vector<double>> result(output.size(), std::vector<double>(dEdt.size(), 0.0));

    for (int i = 0; i < output.size(); i++) {
        for (int j = 0; j < dEdt.size(); j++) {
            result[i][j] = output[i] * dEdt[j];
        }
    }

    return result;
}

std::vector<std::vector<double>> matrix_multiply_scalar(double number,
                                                        const std::vector<std::vector<double>>& matrix) {
    std::vector<std::vector<double>> result(matrix.size(), std::vector<double>(matrix[0].size(), 0.0));

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            result[i][j] = number * matrix[i][j];
        }
    }
    return result;
}

std::vector<std::vector<double>> matrix_subtract(const std::vector<std::vector<double>>& matrix1,
                                                 const std::vector<std::vector<double>>& matrix2) {
    std::vector<std::vector<double>> result(matrix1.size(), std::vector<double>(matrix1[0].size(), 0.0));

    for (int i = 0; i < matrix1.size(); i++) {
        for (int j = 0; j < matrix1[0].size(); j++) {
            result[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }
    return result;
}

std::vector<double> vector_subtract(const std::vector<double>& vector1, const std::vector<double>& vector2) {
    std::vector<double> result(vector1.size());

    for (int i = 0; i < vector1.size(); i++) {
        result[i] = vector1[i] - vector2[i];
    }
    return result;
}