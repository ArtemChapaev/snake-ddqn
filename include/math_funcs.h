#include <algorithm>
#include <cmath>
#include <vector>

std::vector<double> relu(const std::vector<double> &);

std::vector<double> relu_deriv(const std::vector<double> &);

std::vector<double> softmax(const std::vector<double> &);

std::vector<double> softmax_deriv(const std::vector<double> &);

std::vector<std::vector<double>> transpose_m(const std::vector<std::vector<double>> &);

std::vector<std::vector<double>> m_dot_m(const std::vector<std::vector<double>> &,
                                         const std::vector<std::vector<double>> &);

std::vector<double> m_dot_v(const std::vector<std::vector<double>> &matrix, const std::vector<double> &vector);

std::vector<double> v_mul_v(const std::vector<double> &, const std::vector<double> &);

std::vector<std::vector<double>> m_mul_scal(const std::vector<std::vector<double>> &, double number);

std::vector<double> v_mul_scal(const std::vector<double> &, double);

std::vector<std::vector<double>> m_plus_m(const std::vector<std::vector<double>> &,
                                          const std::vector<std::vector<double>> &);

std::vector<double> v_plus_v(const std::vector<double> &, const std::vector<double> &);

std::vector<std::vector<double>> m_minus_m(const std::vector<std::vector<double>> &,
                                           const std::vector<std::vector<double>> &);

std::vector<double> v_minus_v(const std::vector<double> &, const std::vector<double> &);
