#pragma once

#include "control.h"
#include "mapModel.h"
#include "perceptron.h"
#include "snake.h"

const double kEpsilonCoef = 0.99999;

class aiControl : public Control {
   public:
    aiControl(std::vector<int> layers, double learning_rate = 0.01, double gamma = 0.99,
              double epsilon = 0.7);

    Keys get_direction(const State&, Keys, unsigned, const State&);

   private:
    double epsilon;
    Network1 network;
};
