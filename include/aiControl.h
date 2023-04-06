#pragma once

#include "control.h"
#include "perceptron.h"
#include "snake.h"

class aiControl : public Control {
   public:
    aiControl(std::vector<int> layers, double learning_rate = 0.01, double gamma = 0.99,
              double epsilon = 0.7);

    Keys get_direction(std::vector<double>, Keys, unsigned, std::vector<double>);

   private:
    double epsilon;
    Network1 network;
};
