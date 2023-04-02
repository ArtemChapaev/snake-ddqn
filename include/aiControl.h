#pragma once

#include "control.h"
#include "neuralNetwork.h"
#include "snake.h"

class aiControl : public Control {
   public:
    aiControl() : epsilon(0.5) {}

    Keys get_direction(unsigned, Keys, unsigned, unsigned);

   private:
    double epsilon;
    Network1 network;
};