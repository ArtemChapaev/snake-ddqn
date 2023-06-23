#pragma once

#include <utility>

#include "control.h"
#include "mapModel.h"
#include "simpleNN.h"
#include "snake.h"

const unsigned kBatchSize = 50;
const unsigned kStepsForNetworkSwap = 100;

struct Sample {
    Sample() : a(Keys::right), r(0.0) {}

    Sample(std::vector<double> s, Keys a, double r, std::vector<double> n_s)
        : s(std::move(s)), a(a), r(r), n_s(std::move(n_s)) {}

    std::vector<double> s;
    Keys a;
    double r;
    std::vector<double> n_s;
};

const double kEpsilonCoef = 0.9999;

const std::string kWeightsFile = "weights.txt";
const std::string kBiasesFile = "biases.txt";

class AiControl : public Control {
   public:
    AiControl(std::vector<int> &layers, bool use_batch = true, double epsilon = 0.6, double learning_rate = 0.0001,
              double gamma = 0.98);

    void train_nn(const State &, Keys, double, const State &);
    Keys get_direction(const State &, Keys, bool);

    void set_use_batch(bool);

    void save_network_hyperparameters();
    int load_network_hyperparameters();

   private:
    SimpleNN network;
    SimpleNN target_network;
    double epsilon;
    bool use_batch;

    std::vector<Sample> samples;
    unsigned n_steps;
};
