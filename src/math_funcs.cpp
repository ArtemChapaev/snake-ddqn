#include "math_funcs.h"

std::vector<double> relu(const std::vector<double> &vector) {
    std::vector<double> result(vector.size());

    for (int i = 0; i < vector.size(); i++) {
        result[i] = std::max(0.0, vector[i]);
    }

    return result;
}

std::vector<double> relu_deriv(const std::vector<double> &vector) {
    std::vector<double> result(vector.size());
    for (int i = 0; i < vector.size(); i++) {
        vector[i] < 0 ? result[i] = 0 : result[i] = 1;
    }
    return result;
}

std::vector<double> softmax(const std::vector<double> &vector) {
    std::vector<double> result(vector.size());
    double sum = 0.0;

    for (int i = 0; i < vector.size(); i++) {
        sum += std::exp(vector[i]);
    }

    for (int i = 0; i < vector.size(); i++) {
        result[i] = std::exp(vector[i]) / sum;
    }

    return result;
}

std::vector<double> softmax_deriv(const std::vector<double> &vector) {
    std::vector<double> ones(vector.size(), 1.0);

    return v_mul_v(vector, v_minus_v(ones, vector));
}

std::vector<std::vector<double>> transpose_m(const std::vector<std::vector<double>> &matrix) {
    std::vector<std::vector<double>> result(matrix[0].size(), std::vector<double>(matrix.size()));

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            result[j][i] = matrix[i][j];
        }
    }

    return result;
}

std::vector<std::vector<double>> m_dot_m(const std::vector<std::vector<double>> &matrix1,
                                         const std::vector<std::vector<double>> &matrix2) {
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

std::vector<double> m_dot_v(const std::vector<std::vector<double>> &matrix,
                            const std::vector<double> &vector) {
    std::vector<double> result(matrix.size());

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < vector.size(); j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }

    return result;
}

std::vector<double> v_mul_v(const std::vector<double> &vector1, const std::vector<double> &vector2) {
    std::vector<double> result(vector1.size());
    for (int i = 0; i < vector1.size(); ++i) {
        result[i] = vector1[i] * vector2[i];
    }
    return result;
}

std::vector<std::vector<double>> m_mul_scal(const std::vector<std::vector<double>> &matrix, double number) {
    std::vector<std::vector<double>> result(matrix.size(), std::vector<double>(matrix[0].size()));

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            result[i][j] = number * matrix[i][j];
        }
    }
    return result;
}

std::vector<double> v_mul_scal(const std::vector<double> &vector, double num) {
    std::vector<double> result(vector.size());

    for (int i = 0; i < vector.size(); i++) {
        result[i] = num * vector[i];
    }

    return result;
}

std::vector<std::vector<double>> m_plus_m(const std::vector<std::vector<double>> &matrix1,
                                          const std::vector<std::vector<double>> &matrix2) {
    std::vector<std::vector<double>> result(matrix1.size(), std::vector<double>(matrix1[0].size()));

    for (int i = 0; i < matrix1.size(); i++) {
        for (int j = 0; j < matrix1[i].size(); j++) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }

    return result;
}

std::vector<double> v_plus_v(const std::vector<double> &vector1, const std::vector<double> &vector2) {
    std::vector<double> result(vector1.size());

    for (int i = 0; i < vector1.size(); i++) {
        result[i] = vector1[i] + vector2[i];
    }

    return result;
}

std::vector<std::vector<double>> m_minus_m(const std::vector<std::vector<double>> &matrix1,
                                           const std::vector<std::vector<double>> &matrix2) {
    std::vector<std::vector<double>> result(matrix1.size(), std::vector<double>(matrix1[0].size()));

    for (int i = 0; i < matrix1.size(); i++) {
        for (int j = 0; j < matrix1[0].size(); j++) {
            result[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }
    return result;
}

std::vector<double> v_minus_v(const std::vector<double> &vector1, const std::vector<double> &vector2) {
    std::vector<double> result(vector1.size());

    for (int i = 0; i < vector1.size(); i++) {
        result[i] = vector1[i] - vector2[i];
    }
    return result;
}
