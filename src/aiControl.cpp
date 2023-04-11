#include "aiControl.h"

aiControl::aiControl(std::vector<int> layers, double learning_rate, double gamma, double epsilon)
    : network(layers, learning_rate, gamma), epsilon(epsilon) {}

Keys aiControl::get_direction(const State &s, Keys a, unsigned r, const State &n_s) {
    auto st = state_struct_to_vector(s);
    auto n_st = state_struct_to_vector(n_s);

    network.backward(st, a, r, n_st);

    Qvalues next_qvalues = vector_to_qvalues_struct(network.forward(n_st));

    Keys next_action = Keys::up;
    double max_qvalue = 0;

    // e-greedy algorithm
    if ((rand() % 10) / 10.0 < epsilon) {
        next_action = static_cast<Keys>(rand() % 4);  // rand() % 4 because we pick random direction
    } else {
        std::tie(max_qvalue, next_action) = find_max_qvalue(next_qvalues);
    }
    // NEED CONSTANT-VALUE
    epsilon *= kEpsilonCoef;

    return next_action;
}
