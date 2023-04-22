#pragma once

#include "control.h"
#include "mapModel.h"
#include "simpleNN.h"
#include "snake.h"

const double kEpsilonCoef = 0.99999;

const std::string kWeightsFile = "weights.txt";
const std::string kBiasesFile = "biases.txt";

class aiControl : public Control {
   public:
    aiControl(std::vector<int> layers, double learning_rate = 0.01, double gamma = 0.99,
              double epsilon = 0.4);

    void train_nn(const State&, Keys, double, const State &);
    Keys get_direction(const State&, Keys);
    void save_network_hyperparameters();
    int load_network_hyperparameters();

   private:
    SimpleNN network;
    double epsilon;
};
