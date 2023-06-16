#include "mathFuncs.h"

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
        result[i] = vector[i] < 0 ?  0 : 1;
    }
    return result;
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
    if (matrix1.empty() || matrix2.empty()) {
        throw std::invalid_argument("at least one matrix is empty (m_dot_m)");
    }

    if (matrix1[0].size() != matrix2.size()) {
        throw std::invalid_argument("matrices are not compatible for dot (m_dot_m)");
    }

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

std::vector<double> v_dot_m(const std::vector<double> &vector,
                            const std::vector<std::vector<double>> &matrix) {
    if (matrix.empty() || matrix[0].empty()) {
        throw std::invalid_argument("matrix is empty (v_dot_m)");
    }

    if (vector.empty()) {
        throw std::invalid_argument("vector is empty (v_dot_m)");
    }

    if (matrix.size() != vector.size()) {
        std::string sizes = std::to_string(vector.size()) + " and " + std::to_string(matrix.size()) + "x" +
                            std::to_string(matrix[0].size());
        throw std::invalid_argument("vector and matrix are not compatible for multiplication (v_dot_m): " +
                                    sizes);
    }

    std::vector<double> result(matrix[0].size());

    for (int i = 0; i < matrix[0].size(); i++) {    //           [4 5
        for (int j = 0; j < vector.size(); j++) {   // [1 2 3] *  6 7   =  [40, 46]
            result[i] += matrix[j][i] * vector[j];  //            8 9]
        }
    }

    return result;
}

std::vector<double> v_mul_v(const std::vector<double> &vector1, const std::vector<double> &vector2) {
    if (vector1.size() != vector2.size()) {
        std::string sizes = std::to_string(vector1.size()) + " and " + std::to_string(vector2.size());
        throw std::invalid_argument("vectors have different sizes (v_mul_v) " + sizes);
    }

    std::vector<double> result(vector1.size());
    for (int i = 0; i < vector1.size(); ++i) {
        result[i] = vector1[i] * vector2[i];
    }
    return result;
}

std::vector<std::vector<double>> m_mul_scal(const std::vector<std::vector<double>> &matrix, double number) {
    if (std::isnan(number)) {
        throw std::invalid_argument("number is NaN (m_mul_scal)");
    }
    if (std::isinf(number)) {
        throw std::invalid_argument("number is Inf (m_mul_scal)");
    }

    std::vector<std::vector<double>> result(matrix.size(), std::vector<double>(matrix[0].size()));

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            if (std::isnan(number * matrix[i][j])) {
                throw std::invalid_argument("number * matrix[i][j] is NaN (m_mul_scal)");
            }
            if (std::isinf(number * matrix[i][j])) {
                throw std::invalid_argument("number * matrix[i][j] is Inf (m_mul_scal)");
            }
            result[i][j] = number * matrix[i][j];
        }
    }
    return result;
}

std::vector<double> v_mul_scal(const std::vector<double> &vector, double num) {
    if (std::isnan(num)) {
        throw std::invalid_argument("number is NaN (v_mul_scal)");
    }
    if (std::isinf(num)) {
        throw std::invalid_argument("number is Inf (v_mul_scal)");
    }

    std::vector<double> result(vector.size());

    for (int i = 0; i < vector.size(); i++) {
        result[i] = num * vector[i];
    }

    return result;
}

std::vector<std::vector<double>> m_plus_m(const std::vector<std::vector<double>> &matrix1,
                                          const std::vector<std::vector<double>> &matrix2) {
    if (matrix1.size() != matrix2.size() || matrix1[0].size() != matrix2[0].size()) {
        throw std::invalid_argument("matrices have different sizes (m_plus_m)");
    }

    std::vector<std::vector<double>> result(matrix1.size(), std::vector<double>(matrix1[0].size()));

    for (int i = 0; i < matrix1.size(); i++) {
        for (int j = 0; j < matrix1[i].size(); j++) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }

    return result;
}

std::vector<double> v_plus_v(const std::vector<double> &vector1, const std::vector<double> &vector2) {
    if (vector1.size() != vector2.size()) {
        throw std::invalid_argument("vectors have different sizes (v_plus_v)");
    }

    std::vector<double> result(vector1.size());

    for (int i = 0; i < vector1.size(); i++) {
        result[i] = vector1[i] + vector2[i];
    }

    return result;
}

std::vector<std::vector<double>> m_minus_m(const std::vector<std::vector<double>> &matrix1,
                                           const std::vector<std::vector<double>> &matrix2) {
    if (matrix1.size() != matrix2.size() || matrix1[0].size() != matrix2[0].size()) {
        throw std::invalid_argument("matrices must have the same size (m_minus_m)");
    }

    std::vector<std::vector<double>> result(matrix1.size(), std::vector<double>(matrix1[0].size()));

    for (int i = 0; i < matrix1.size(); i++) {
        for (int j = 0; j < matrix1[0].size(); j++) {
            result[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }
    return result;
}

std::vector<double> v_minus_v(const std::vector<double> &vector1, const std::vector<double> &vector2) {
    if (vector1.size() != vector2.size()) {
        throw std::invalid_argument("size of two vectors must be the same (v_minus_v)");
    }

    std::vector<double> result(vector1.size());

    for (int i = 0; i < vector1.size(); i++) {
        result[i] = vector1[i] - vector2[i];
    }
    return result;
}
