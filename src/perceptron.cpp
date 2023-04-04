#include "perceptron.h"

void Network1::backward(unsigned s, Keys a, unsigned r, unsigned n_s) {
    // calculations for last layer
    std::vector<double> dEdt_last = calculate_dEdt_last(s, a, r, n_s);
    std::vector<std::vector<double>> dEdW_last = calculate_dEdW(outputs[num_layers - 1], dEdt_last);
    std::vector<double> dEdb_last = dEdt_last;

    // stores calculated errors
    std::vector<std::vector<std::vector<double>>> dEdW;
    std::vector<std::vector> dEdb;
    dEdW.push_back(dEdW_last);
    dEdb.push_back(dEdb_last);

    std::vector<double> dEdt_prev = dEdb_last;

    // from penultimate layer to 0s
    for (int i = num_layers - 1; i > 0; i--) {
        std::vector<double> dEdh_i = matrix_multiply_vector(transpose_matrix(weights[i + 1]), dEdt_prev);
        std::vector<double> dEdt_i = multiply_vectors(dEdh_i, relu_deriv(inputs[i]));

        std::vector<std::vector<double>> dEdW_i = calculate_dEdW(outputs[i - 1], dEdt_i);
        std::vector<double> dEdb_i = dEdt_i;
        dEdt_prev = dEdt_i;

        dEdW.push_back(dEdW_i);
        dEdb.push_back(dEdb_i);
    }

    // updating weights
    for (int i = 0; i < num_layers; i++) {
        weights[i] = matrix_subtract(weights[i], matrix_multiply_scalar(learning_rate, dEdW.back()));
        biases[i] = vector_subtract(biases[i], vector_multiply_scalar(learning_rate, dEdb.back()));

        dEdW.pop_back();
        dEdb.pop_back();
    }
}

std::vector<double> Network1::forward(vector<double> input) {
    outputs[0] = input;
    inputs[0] = input;

    for (int i = 1; i < num_layers; i++) {
        inputs[i] = vector_plus_vector(matrix_multiply_vector(weights[i - 1], outputs[i - 1]), biases[i - 1]);
        outputs[i] = relu(inputs[i]);
    }

    // on exit layer function of activation is softmax
    inputs[num_layers] = vector_plus_vector(
        matrix_multiply_vector(weights[num_layers - 1], outputs[num_layers - 1]), biases[num_layers - 1]);
    outputs[num_layers] = softmax(inputs[num_layers]);

    return outputs[num_layers];
}

// example argument: {24, 12, 4} - 2 layers here
Network1::Network1(std::vector<int> layers, double learning_rate) {
    this->layers = layers;
    this->learning_rate = learning_rate;

    num_layers = layers.size() - 1;

    for (int i = 0; i < num_layers; i++) {
        int neuron_from = layers[i];
        int neuron_to = layers[i + 1];

        std::vector<std::vector<double>> neuron;

        // initialize weights with random in [0;1]
        for (int i = 0; i < neuron_from; i++) {
            std::vector<double> neuron_connections;
            for (int j = 0; j < neuron_to; j++) {
                neuron_connections.push_back(static_cast<double>(rand()) / RAND_MAX);
            }
            neuron.push_back(neuron_connections);
        }

        // initialize biases with random in [0;1]
        std::vector<double> b;
        for (int i = 0; i < neuron_to; i++) {
            b.push_back(static_cast<double>(rand()) / RAND_MAX);
        }

        weights.push_back(neuron);
        biases.push_back(b);
    }

    // initialize outputs and errors with zeros
    for (int i = 0; i < num_layers + 1; i++) {
        int nodes = layers[i];

        std::vector<double> o(nodes, 0.0);
        std::vector<double> e(nodes, 0.0);

        outputs.push_back(o);
        inputs.push_back(e);
    }
}

std::tuple<double, Keys> Network1::find_max_qvalue(Qvalues qvalues) {
    double max_qvalue = qvalues.up_qvalue;
    Keys next_action = Keys::up;

    if (next_qvalues.right_qvalue > max_qvalue) {
        max_qvalue = next_qvalues.right_qvalue;
        next_action = Keys::right;
    }
    if (next_qvalues.down_qvalue > max_qvalue) {
        max_qvalue = next_qvalues.down_qvalue;
        next_action = Keys::down;
    }
    if (next_qvalues.left_qvalue > max_qvalue) {
        max_qvalue = next_qvalues.left_qvalue;
        next_action = Keys::left;
    }
    return std::make_tuple(max_qvalue, next_action);
}

double Network1::calculate_dEdt_last(unsigned s, Keys a, unsigned r, unsigned n_s) {
    // find target(y) of current state
    std::vector<double> predicted_next_qvalues = forward(n_s);
    auto [max_qvalue, next_action] = find_max_qvalue(predicted_next_qvalues);
    int gamma = 0.1; // TO DELETE
    double target = r + gamma * max_qvalue;

    // bring to Qvalues for next calculating loss
    // Qvalues target_qvalues{target, target, target, target};

    // calculate sequentially for each dE_dt_last = dE_dz_i * dz_dt_last

    std::vector<double> predicted_current_qvalues = forward(s);

    std::vector<double> dEdt_last;
    for (int i = 0; i < 4; ++i) {
        double dEdz_i = predicted_current_qvalues[i] * (predicted_current_qvalues[i] - target) / 2;
        double dzdt_last = predicted_current_qvalues[i] * (1 - predicted_current_qvalues[i]);
        dEdt_last.push_back(dEdz_i * dzdt_last);
    }

    return dEdt_last;
}