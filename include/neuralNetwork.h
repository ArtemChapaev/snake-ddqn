#pragma once

#include <snake.h>

#include <vector>

class NeuralNetwork {
   public:
    // calculating errors and updating network parameters
    virtual void backward(unsigned s, Keys a, unsigned r, unsigned n_s);

    // takes input values of network and returns an output as vector
    virtual std::vector<double> forward(std::vector<double> input);
}