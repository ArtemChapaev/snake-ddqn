#pragma once

#include <utility>

#include "control.h"
#include "mapModel.h"
#include "simpleNN.h"
#include "snake.h"

const unsigned kBatchSize = 100;

struct Sample {
    Sample() : a(Keys::right), r(0.0) {}

    Sample(std::vector<double> s, Keys a, double r, std::vector<double> n_s)
        : s(std::move(s)), a(a), r(r), n_s(std::move(n_s)) {}

    std::vector<double> s;
    Keys a;
    double r;
    std::vector<double> n_s;
};

const double kEpsilonCoef = 0.99999;

const std::string kWeightsFile = "weights.txt";
const std::string kBiasesFile = "biases.txt";

class AiControl : public Control {
   public:
    AiControl(std::vector<int> layers, double learning_rate = 0.01, double gamma = 0.99, double epsilon = 0.4,
              bool use_batch = false);

    void train_nn(const State &, Keys, double, const State &);
    Keys get_direction(const State &, Keys);

    void set_use_batch(bool);

    void save_network_hyperparameters();
    int load_network_hyperparameters();

   private:
    SimpleNN network;
    double epsilon;
    bool use_batch;

    std::vector<Sample> samples;
};
