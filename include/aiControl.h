#pragma once

#include "control.h"
#include "mapModel.h"
#include "perceptron.h"
#include "snake.h"

const double kEpsilonCoef = 0.99999;

const std::string kWeightsFile = "weights.txt";
const std::string kBiasesFile = "biases.txt";

class aiControl : public Control {
   public:
    aiControl(std::vector<int> layers, double learning_rate = 0.01, double gamma = 0.99,
              double epsilon = 0.7);

    Keys get_direction(const State&, Keys, unsigned, const State&);
    void save_network_hyperparameters();
    int load_network_hyperparameters();

   private:
    double epsilon;
    Perceptron network;
};
