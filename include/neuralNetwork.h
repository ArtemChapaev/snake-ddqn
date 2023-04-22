#pragma once

#include <snake.h>

#include <vector>

struct Qvalues {
    Qvalues(double up = 0, double down = 0, double left = 0, double right = 0)
        : up(up), down(down), left(left), right(right){};

    double up;
    double down;
    double left;
    double right;
};

Qvalues vector_to_qvalues_struct(const std::vector<double> &);
std::tuple<double, Keys> find_max_qvalue(const Qvalues &);

class NeuralNetwork {
   public:
    // calculating errors and updating network parameters
    virtual void backward(std::vector<double> &s, Keys a, double r, std::vector<double> &n_s) = 0;

    // takes input values of network and returns an output as vector
    virtual std::vector<double> forward(std::vector<double> &input) = 0;
};
