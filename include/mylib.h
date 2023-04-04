#include <algorithm>
#include <cmath>
#include <vector>

std::vector<double> relu(std::vector<double>& vec);

std::vector<double> relu_deriv(std::vector<double>& vec);

std::vector<double> softmax(std::vector<double>& vec);

std::vector<double> matrix_multiply_vector(std::vector<std::vector<double>>& matrix,
                                           std::vector<double>& vector);

std::vector<std::vector<double>> matrix_plus_matrix(std::vector<std::vector<double>>& matrix1,
                                                    std::vector<std::vector<double>>& matrix2);

std::vector<std::vector<double>> matrix_multiply_matrix(std::vector<std::vector<double>>& matrix1,
                                                        std::vector<std::vector<double>>& matrix2);

std::vector<std::vector<double>> transpose_matrix(std::vector<std::vector<double>>& matrix);

std::vector<double> vector_plus_vector(const std::vector<double>& vec1, const std::vector<double>& vec2);

std::vector<double> vector_multiply_scalar(double num, std::vector<double>& vector);

std::vector<double> multiply_vectors(std::vector<double>& vec1, std::vector<double>& vec2);

std::vector<std::vector<double>> calculate_dEdW(std::vector<double> output, std::vector<double> dEdt);

std::vector<std::vector<double>> matrix_multiply_scalar(double number,
                                                        std::vector<std::vector<double>> matrix);

std::vector<std::vector<double>> matrix_subtract(std::vector<std::vector<double>> matrix1,
                                                 std::vector<std::vector<double>> matrix2);

std::vector<double> vector_subtract(std::vector<double> vector1, std::vector<double> vector2);