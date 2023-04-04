#pragma once

#include <snake.h>

#include <vector>

class NeuralNetwork {
   public:
    // calculating errors and updating network parameters
    virtual void backward(std::vector<double> s, Keys a, unsigned r, std::vector<double> n_s) = 0;

    // takes input values of network and returns an output as vector
    virtual std::vector<double> forward(std::vector<double> input) = 0;
};
