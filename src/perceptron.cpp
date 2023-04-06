#include "perceptron.h"

std::tuple<double, Keys> find_max_qvalue(std::vector<double> &qvalues) {
    double max_qvalue = qvalues[0];
    Keys next_action = Keys::up;

    if (qvalues[1] > max_qvalue) {
        max_qvalue = qvalues[1];
        next_action = Keys::right;
    }
    if (qvalues[2] > max_qvalue) {
        max_qvalue = qvalues[2];
        next_action = Keys::down;
    }
    if (qvalues[3] > max_qvalue) {
        max_qvalue = qvalues[3];
        next_action = Keys::left;
    }
    return std::make_tuple(max_qvalue, next_action);
}

// example "layers" argument: {24, 12, 4} - 2 layers here
Network1::Network1(std::vector<int> &layers, double learning_rate, double gamma)
    : layers(layers), learning_rate(learning_rate), gamma(gamma) {
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

        std::vector<double> o(nodes);
        std::vector<double> e(nodes);

        outputs.push_back(o);
        inputs.push_back(e);
    }
}

void Network1::backward(std::vector<double> &s, Keys a, unsigned r, std::vector<double> &n_s) {
    // calculations for last layer
    std::vector<double> dEdt_last = calculate_dEdt_last(s, a, r, n_s);
    std::vector<std::vector<double>> dEdW_last = calculate_dEdW(outputs[num_layers - 1], dEdt_last);
    std::vector<double> dEdb_last = dEdt_last;

    // stores calculated errors
    std::vector<std::vector<std::vector<double>>> dEdW;
    std::vector<std::vector<double>> dEdb;
    dEdW.push_back(dEdW_last);
    dEdb.push_back(dEdb_last);

    std::vector<double> dEdt_prev = dEdb_last;

    // from penultimate layer to 0s
    for (int i = num_layers - 2; i > 0; i--) {
        std::vector<double> dEdh_i = m_mul_v(transpose_m(weights[i + 1]), dEdt_prev);
        std::vector<double> dEdt_i = v_mul_v(dEdh_i, relu_deriv(inputs[i]));

        std::vector<std::vector<double>> dEdW_i = calculate_dEdW(outputs[i - 1], dEdt_i);
        std::vector<double> dEdb_i = dEdt_i;
        dEdt_prev = dEdt_i;

        dEdW.push_back(dEdW_i);
        dEdb.push_back(dEdb_i);
    }

    // updating weights
    for (int i = 0; i < num_layers - 1; i++) {
        weights[i] = m_minus_m(weights[i], m_mul_scal(dEdW.back(), learning_rate));
        biases[i] = v_minus_v(biases[i], v_mul_scal(dEdb.back(), learning_rate));

        dEdW.pop_back();
        dEdb.pop_back();
    }
}

std::vector<double> Network1::forward(std::vector<double> &input) {
    outputs[0] = input;
    inputs[0] = input;

    for (int i = 1; i < num_layers; i++) {
        inputs[i] = v_plus_v(m_mul_v(weights[i - 1], outputs[i - 1]), biases[i - 1]);
        outputs[i] = relu(inputs[i]);
    }

    // on exit layer function of activation is softmax
    inputs[num_layers] =
        v_plus_v(m_mul_v(weights[num_layers - 1], outputs[num_layers - 1]), biases[num_layers - 1]);
    outputs[num_layers] = softmax(inputs[num_layers]);

    return outputs[num_layers];
}

std::vector<double> Network1::calculate_dEdt_last(std::vector<double> &s, Keys a, unsigned r,
                                                  std::vector<double> &n_s) {
    // find target(y) of current state
    std::vector<double> predicted_next_qvalues = forward(n_s);
    auto [max_qvalue, _] = find_max_qvalue(predicted_next_qvalues);

    double predicted_qvalue = forward(s)[a];
    double target = r + gamma * max_qvalue;

    std::vector<double> dEdt_last = std::vector<double>(4);
    dEdt_last[a] =
        2 * (predicted_qvalue - target) * predicted_qvalue * predicted_qvalue * (1 - predicted_qvalue);

    return dEdt_last;
}

std::vector<std::vector<double>> Network1::calculate_dEdW(const std::vector<double> &output,
                                                          const std::vector<double> &dEdt) {
    std::vector<std::vector<double>> result(output.size(), std::vector<double>(dEdt.size()));

    for (int i = 0; i < output.size(); i++) {
        for (int j = 0; j < dEdt.size(); j++) {
            result[i][j] = output[i] * dEdt[j];
        }
    }

    return result;
}
