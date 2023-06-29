#include "simpleNN.h"

std::vector<double> get_random_vector_from_range(int n, double a, double b);

SimpleNN::SimpleNN(std::vector<int> &layers, double learning_rate, double gamma)
    : layers(layers), num_layers(layers.size() - 1), learning_rate(learning_rate), gamma(gamma) {
    weights.resize(num_layers);
    biases.resize(num_layers);

    int neuron_from = layers[0];
    int neuron_to = layers[1];
    weights[0].resize(neuron_from);

    // init first layer with neuron_from neurons
    for (int i = 0; i < neuron_from; i++) {
        if (i < 8) {
            // bonus neurons
            weights[0][i] = std::move(get_random_vector_from_range(neuron_to, kNetworkInitialValue * 2.0,
                                                                   kNetworkInitialValue * 3.0));
        } else
            // barriers neurons
            weights[0][i] = std::move(
                get_random_vector_from_range(neuron_to, -kNetworkInitialValue, -kNetworkInitialValue / 1.5));
    }
    biases[0] = std::move(std::vector<double>(neuron_to, 0.0));

    // init other layers
    for (int t = 1; t < num_layers; t++) {
        neuron_from = layers[t];
        neuron_to = layers[t + 1];
        weights[t].resize(neuron_from);

        for (int i = 0; i < neuron_from; i++) {
            weights[t][i] = std::move(get_random_vector_from_range(neuron_to, -kNetworkInitialValue / 2.0,
                                                                   kNetworkInitialValue / 2.0));
        }
        biases[t] = std::move(std::vector<double>(neuron_to, 0.0));
    }

    // initialize outputs and errors with zeros
    for (int i = 0; i < num_layers + 1; i++) {
        int nodes = layers[i];

        outputs.emplace_back(nodes);
        inputs.emplace_back(nodes);
    }
}

SimpleNN &SimpleNN::operator=(SimpleNN const &other) {
    layers = other.layers;
    num_layers = other.num_layers;

    weights.resize(num_layers);
    biases.resize(num_layers);

    // update all layers
    for (int i = 0; i < num_layers; ++i) {
        int neuron_from = layers[i];
        weights[i].resize(neuron_from);

        for (int j = 0; j < neuron_from; j++) {
            weights[i][j] = other.weights[i][j];
        }
        biases[i] = other.biases[i];
    }

    // update outputs and errors with zeros
    inputs.resize(num_layers + 1);
    outputs.resize(num_layers + 1);
    for (int i = 0; i < num_layers + 1; ++i) {
        inputs = other.inputs;
        outputs = other.outputs;
    }

    return *this;
}

void SimpleNN::backward(std::vector<double> &s, Keys a, double r, std::vector<double> &n_s,
                        NeuralNetwork &target_network) {
    // calculations for last layer
    std::vector<double> dEdt_last = calculate_dEdt_last(s, a, r, n_s, target_network);
    std::vector<std::vector<double>> dEdW_last = calculate_dEdW(outputs[num_layers - 1], dEdt_last);
    std::vector<double> dEdb_last = dEdt_last;

    // stores calculated errors
    std::vector<std::vector<std::vector<double>>> dEdW;
    std::vector<std::vector<double>> dEdb;
    dEdW.push_back(dEdW_last);
    dEdb.push_back(dEdb_last);

    std::vector<double> dEdt_prev = dEdb_last;

    // from penultimate layer to 0s
    for (int i = num_layers - 2; i >= 0; i--) {
        std::vector<double> dEdh_i = v_dot_m(dEdt_prev, transpose_m(weights[i + 1]));
        std::vector<double> dEdt_i = v_mul_v(dEdh_i, relu_deriv(inputs[i + 1]));

        std::vector<std::vector<double>> dEdW_i = calculate_dEdW(outputs[i], dEdt_i);
        std::vector<double> dEdb_i = dEdt_i;
        dEdt_prev = dEdt_i;

        dEdW.push_back(dEdW_i);
        dEdb.push_back(dEdb_i);
    }

    // updating weights
    for (int i = 0; i <= num_layers - 1; i++) {
        weights[i] = m_plus_m(weights[i], m_mul_scal(dEdW.back(), learning_rate));
        biases[i] = v_plus_v(biases[i], v_mul_scal(dEdb.back(), learning_rate));

        dEdW.pop_back();
        dEdb.pop_back();
    }
}

std::vector<double> SimpleNN::forward(std::vector<double> &input) {
    outputs[0] = input;
    inputs[0] = input;

    for (int i = 1; i < num_layers + 1; i++) {
        inputs[i] = v_plus_v(v_dot_m(outputs[i - 1], weights[i - 1]), biases[i - 1]);
        outputs[i] = relu(inputs[i]);
    }

    // on exit layer function of activation is softmax
    // inputs[num_layers] =
    //     v_plus_v(v_dot_m(outputs[num_layers - 1], weights[num_layers - 1]), biases[num_layers - 1]);
    // outputs[num_layers] = softmax(inputs[num_layers]);

    return outputs[num_layers];
}

std::vector<double> SimpleNN::calculate_dEdt_last(std::vector<double> &s, Keys a, double r,
                                                  std::vector<double> &n_s, NeuralNetwork &target_network) {
    // find target(y) of current state
    struct Qvalues predicted_next_qvalues = vector_to_qvalues_struct(target_network.forward(n_s));
    auto [max_qvalue, _] = find_max_qvalue(predicted_next_qvalues);
    double target = r + gamma * max_qvalue;

    double predicted_qvalue = forward(s)[a];

    std::vector<double> dEdt_last = std::vector<double>(4);
    double grad = (target - predicted_qvalue);
    if (!std::isnan(grad)) {
        dEdt_last[a] = grad;
    }

    return dEdt_last;
}

std::vector<std::vector<double>> SimpleNN::calculate_dEdW(const std::vector<double> &output,
                                                          const std::vector<double> &dEdt) {
    std::vector<std::vector<double>> result(output.size(), std::vector<double>(dEdt.size()));

    for (int i = 0; i < output.size(); i++) {
        for (int j = 0; j < dEdt.size(); j++) {
            result[i][j] = output[i] * dEdt[j];
        }
    }

    return result;
}

std::vector<std::vector<std::vector<double>>> SimpleNN::get_weights() {
    return weights;
}

std::vector<std::vector<double>> SimpleNN::get_biases() {
    return biases;
}

void SimpleNN::set_weights(const std::vector<std::vector<std::vector<double>>> &_weights) {
    weights = _weights;
}

void SimpleNN::set_biases(const std::vector<std::vector<double>> &_biases) {
    biases = _biases;
}

Qvalues vector_to_qvalues_struct(const std::vector<double> &qvalues) {
    struct Qvalues result;
    result.up = qvalues[0];
    result.right = qvalues[1];
    result.down = qvalues[2];
    result.left = qvalues[3];
    return result;
}

std::tuple<double, Keys> find_max_qvalue(const Qvalues &qvalues) {
    double max_qvalue = qvalues.up;
    Keys next_action = Keys::up;

    if (qvalues.right > max_qvalue) {
        max_qvalue = qvalues.right;
        next_action = Keys::right;
    }
    if (qvalues.down > max_qvalue) {
        max_qvalue = qvalues.down;
        next_action = Keys::down;
    }
    if (qvalues.left > max_qvalue) {
        max_qvalue = qvalues.left;
        next_action = Keys::left;
    }
    return std::make_tuple(max_qvalue, next_action);
}

double get_number_from_range(double a, double b) {
    if (b != 0.0) {
        return a + (b - a) * static_cast<double>(rand()) / RAND_MAX;
    }
    return a * static_cast<double>(rand()) / RAND_MAX;
}

std::vector<double> get_random_vector_from_range(int n, double a, double b) {
    std::vector<double> res(n);
    for (int i = 0; i < n; ++i) {
        res[i] = get_number_from_range(a, b);
    }
    return res;
}
