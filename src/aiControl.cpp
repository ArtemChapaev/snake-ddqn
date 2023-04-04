#include "aiControl.h"

aiControl::aiControl(std::vector<int> layers, double learning_rate = 0.01, double gamma = 0.99,
                     double epsilon = 0.01)
    : network(layers, learning_rate, gamma), epsilon(epsilon) {}

Keys aiControl::get_direction(std::vector<double> s, Keys a, unsigned r, std::vector<double> n_s) {
    network.backward(s, a, r, n_s);

    std::vector<double> next_qvalues = network.forward(n_s);

    Keys next_action = Keys::up;
    double max_qvalue = 0;

    // e-greedy algorithm
    if ((rand() % 10) / 10 < epsilon) {
        next_action = static_cast<Keys>(rand() % 4);  // rand() % 4 because we pick random direction
    } else {
        std::tie(max_qvalue, next_action) = network.find_max_qvalue(next_qvalues);
    }
    epsilon *= 0.99;

    return next_action;
}
