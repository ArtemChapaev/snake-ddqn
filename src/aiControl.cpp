#include "aiControl.h"

aiControl::aiControl(std::vector<int> layers, double learning_rate, double gamma, double epsilon)
        : network(layers, learning_rate, gamma), epsilon(epsilon) {}

void aiControl::train_nn(const State &s, Keys a, double r, const State &n_s) {
    auto st = state_struct_to_vector(s);
    auto n_st = state_struct_to_vector(n_s);

    network.backward(st, a, r, n_st);
}

Keys aiControl::get_direction(const State &s, Keys last_direction) {
    auto st = state_struct_to_vector(s);

    Keys next_action = Keys::up;
    // e-greedy algorithm
    if ((rand() % 10) / 10.0 < epsilon) {
        // use only if next_action isn't opposite last action(a)
        bool is_good_dir = false;
        while (!is_good_dir) {
            // rand() % 4 because we pick random direction
            next_action = static_cast<Keys>(rand() % 4);
            if (check_direction(last_direction, next_action)) {
                is_good_dir = true;
            }
        }
    } else {
        Qvalues qvalues = vector_to_qvalues_struct(network.forward(st));

        double max_qvalue = 0;
        std::tie(max_qvalue, next_action) = find_max_qvalue(qvalues);
    }

    epsilon *= kEpsilonCoef;

    return next_action;
}

void aiControl::save_network_hyperparameters() {
    std::vector<std::vector<std::vector<double>>> weights = network.get_weights();
    std::vector<std::vector<double>> biases = network.get_biases();

    std::ofstream file_weights(kWeightsFile);
    if (!file_weights) {
        throw std::ios_base::failure("invalid weights file");
    }

    for (const auto &outer_vec: weights) {
        for (const auto &middle_vec: outer_vec) {
            for (const auto &value: middle_vec) {
                file_weights << value << " ";
            }
            file_weights << std::endl;
        }
        file_weights << std::endl;
    }

    file_weights.close();

    std::ofstream file_biases(kBiasesFile);
    if (!file_biases) {
        throw std::ios_base::failure("invalid biases file");
    }

    for (const auto &outer_vec: biases) {
        for (const auto &value: outer_vec) {
            file_biases << value << " ";
        }
        file_biases << std::endl << std::endl;
    }

    file_biases.close();
}

int aiControl::load_network_hyperparameters() {
    std::ifstream file_biases(kBiasesFile);
    if (!file_biases) {
        return 0;
    }

    std::vector<std::vector<double>> biases;
    std::vector<double> b_outer_vec;
    double b_value = 0;
    std::string b_line;

    while (std::getline(file_biases, b_line)) {
        std::stringstream ss(b_line);
        while (ss >> b_value) {
            b_outer_vec.push_back(b_value);
        }
        if (!b_outer_vec.empty()) {
            biases.push_back(b_outer_vec);
            b_outer_vec.clear();
        }
    }

    file_biases.close();
    network.set_biases(biases);

    std::ifstream file_weights(kWeightsFile);
    if (!file_weights) {
        return 0;
    }

    std::vector<std::vector<std::vector<double>>> weights;
    std::vector<std::vector<double>> w_outer_vec;
    std::vector<double> w_middle_vec;
    double w_value = 0;
    std::string w_line;

    while (std::getline(file_weights, w_line)) {
        std::stringstream ss(w_line);
        while (ss >> w_value) {
            w_middle_vec.push_back(w_value);
        }
        if (!w_middle_vec.empty()) {
            w_outer_vec.push_back(w_middle_vec);
            w_middle_vec.clear();
        } else {
            weights.push_back(w_outer_vec);
            w_outer_vec.clear();
        }
    }

    file_weights.close();
    network.set_weights(weights);
    return 1;
}
