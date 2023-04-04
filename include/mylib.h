#include <algorithm>
#include <cmath>
#include <vector>

std::vector<double> relu(const std::vector<double>& vec);

std::vector<double> relu_deriv(const std::vector<double>& vec);

std::vector<double> softmax(const std::vector<double>& vec);

std::vector<double> matrix_multiply_vector(const std::vector<std::vector<double>>& matrix,
                                           const std::vector<double>& vector);

std::vector<std::vector<double>> matrix_plus_matrix(const std::vector<std::vector<double>>& matrix1,
                                                    const std::vector<std::vector<double>>& matrix2);

std::vector<std::vector<double>> matrix_multiply_matrix(const std::vector<std::vector<double>>& matrix1,
                                                        const std::vector<std::vector<double>>& matrix2);

std::vector<std::vector<double>> transpose_matrix(const std::vector<std::vector<double>>& matrix);

std::vector<double> vector_plus_vector(const std::vector<double>& vec1, const std::vector<double>& vec2);

std::vector<double> vector_multiply_scalar(double num, const std::vector<double>& vector);

std::vector<double> multiply_vectors(const std::vector<double>& vec1, const std::vector<double>& vec2);

std::vector<std::vector<double>> calculate_dEdW(const std::vector<double>& output,
                                                const std::vector<double>& dEdt);

std::vector<std::vector<double>> matrix_multiply_scalar(double number,
                                                        const std::vector<std::vector<double>>& matrix);

std::vector<std::vector<double>> matrix_subtract(const std::vector<std::vector<double>>& matrix1,
                                                 const std::vector<std::vector<double>>& matrix2);

std::vector<double> vector_subtract(const std::vector<double>& vector1, const std::vector<double>& vector2);