#include "perceptron.h"

void Network1::backward(unsigned s, Keys a, unsigned r, unsigned n_s) {
    std::vector<double> dEdt_last = calculate_dEdt_last(s, a, r, n_s);
    std::vector<double> dEdW_last = multiply_vectors(outputs[num_layers - 2], dEdt_last);
    std::vector<double> dEdb_last = dEdt_last;

    std::vector<double> dEdt_prev = dEdb_last;
    // TODO
    // for (int i = num_layers - 2; i >= 0; i--) {
    //     std::vector<double> dEdh = matrix_multiply_vector(transpose_matrix(weights[i + 1]), dEdt_prev);
    //     std::vector<double> dEdt = multiply_vectors(dEdh, relu_deriv(inputs[i]));

    //      dEdt_prev = dEdt;
    // }
}

std::vector<double> Network1::forward(vector<double> input) {
    outputs[0] = input;
    inputs[0] = input;

    for (int i = 0; i < num_layers - 2; i++) {
        inputs[i + 1] = vector_plus_vector(matrix_multiply_vector(weights[i], outputs[i]), biases[i]);
        outputs[i + 1] = relu(inputs[i + 1]);
    }

    // on exit layer function of activation is softmax
    inputs[num_layers - 1] = vector_plus_vector(
        matrix_multiply_vector(weights[num_layers - 2], outputs[num_layers - 2]), biases[num_layers - 2]);
    outputs[num_layers - 1] = softmax(inputs[num_layers - 1]);

    return outputs[num_layers - 1];
}

// example argument: {24, 12, 4} - 3 layers here
Network1::Network1(std::vector<int> layers) {
    this->layers = layers;
    num_layers = layers.size();

    for (int i = 0; i < num_layers - 1; i++) {
        int rows = layers[i + 1];
        int cols = layers[i];

        std::vector<std::vector<double>> neuron;

        // initialize weights with random in [0;1]
        for (int i = 0; i < cols; i++) {
            std::vector<double> neuron_connections;
            for (int j = 0; j < rows; j++) {
                neuron_connections.push_back(static_cast<double>(rand()) / RAND_MAX);
            }
            neuron.push_back(neuron_connections);
        }

        // initialize biases with random in [0;1]
        std::vector<double> b;
        for (int i = 0; i < rows; i++) {
            b.push_back(static_cast<double>(rand()) / RAND_MAX);
        }

        weights.push_back(neuron);
        biases.push_back(b);
    }

    // initialize outputs and errors with zeros
    for (int i = 0; i < num_layers; i++) {
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
    double target = r + gamma * max_qvalue;

    // bring to Qvalues for next calculating loss
    // Qvalues target_qvalues{target, target, target, target};

    // calculate sequentially for each dE_dt_last = dE_dz_i * dz_dt_last

    std::vector<double> predicted_current_qvalues = forward(s);

    std::vector<double> dEdt_last;
    for (int i = 0; i < 4; ++i) {
        double dE_dz_i = predicted_current_qvalues[i] * (predicted_current_qvalues[i] - target) / 2;
        double dz_dt_last = predicted_current_qvalues[i] * (1 - predicted_current_qvalues[i]);
        dEdt_last.push_back(dE_dz_i * dz_dt_last);
    }

    return dEdt_last;
}