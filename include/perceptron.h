#include <math_funcs.h>
#include <neuralNetwork.h>
#include <snake.h>

#include <cstdlib>
#include <vector>

std::tuple<double, Keys> find_max_qvalue(std::vector<double> &);

class Network1 : public NeuralNetwork {
   public:
    Network1(std::vector<int> &layers, double learning_rate = 0.01, double gamma = 0.99);
    void backward(std::vector<double> &, Keys, unsigned, std::vector<double> &) override;
    std::vector<double> forward(std::vector<double> &) override;

   private:
    std::vector<double> calculate_dEdt_last(std::vector<double> &, Keys, unsigned, std::vector<double> &);

    std::vector<std::vector<double>> calculate_dEdW(const std::vector<double> &, const std::vector<double> &);

    std::vector<int> layers;
    int num_layers;

    std::vector<std::vector<std::vector<double>>> weights;
    std::vector<std::vector<double>> biases;

    std::vector<std::vector<double>> inputs;   // layer input - t
    std::vector<std::vector<double>> outputs;  // layer output - F(t) or h

    double learning_rate;
    double gamma;
};
