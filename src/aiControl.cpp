#include "aiControl.h"

aiControl::aiControl(std::vector<int> layers, double learning_rate, double gamma, double epsilon)
    : network(layers, learning_rate, gamma), epsilon(epsilon) {}

Keys aiControl::get_direction(std::vector<double> s, Keys a, unsigned r, std::vector<double> n_s) {
    network.backward(s, a, r, n_s);

    std::vector<double> next_qvalues = network.forward(n_s);

    Keys next_action = Keys::up;
    double max_qvalue = 0;

    // e-greedy algorithm
    if ((rand() % 10) / 10.0 < epsilon) {
        next_action = static_cast<Keys>(rand() % 4);  // rand() % 4 because we pick random direction
    } else {
        std::tie(max_qvalue, next_action) = find_max_qvalue(next_qvalues);
    }
    // NEED CONSTANT-VALUE
    epsilon *= 0.9999;

    return next_action;
}
