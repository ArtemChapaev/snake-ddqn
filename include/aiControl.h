#pragma once

#include "control.h"
#include "perceptron.h"
#include "snake.h"

class aiControl : public Control {
   public:
    aiControl(std::vector<int> layers, double learning_rate, double gamma, double epsilon);

    Keys get_direction(std::vector<double> s, Keys a, unsigned r, std::vector<double> n_s);

   private:
    double epsilon;
    Network1 network;
};
