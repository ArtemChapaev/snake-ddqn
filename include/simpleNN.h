#include <mathFuncs.h>
#include <neuralNetwork.h>
#include <snake.h>

#include <cstdlib>
#include <vector>

const double kNetworkInitialValue = 0.35;

class SimpleNN : public NeuralNetwork {
   public:
    SimpleNN(std::vector<int> &layers, double learning_rate = 0.01, double gamma = 0.99);

    SimpleNN &operator=(SimpleNN const &);

    void backward(std::vector<double> &, Keys, double, std::vector<double> &, NeuralNetwork &) override;
    std::vector<double> forward(std::vector<double> &) override;

    std::vector<std::vector<std::vector<double>>> get_weights();
    std::vector<std::vector<double>> get_biases();

    void set_weights(const std::vector<std::vector<std::vector<double>>> &);
    void set_biases(const std::vector<std::vector<double>> &);

   private:
    std::vector<double> calculate_dEdt_last(std::vector<double> &, Keys, double, std::vector<double> &,
                                            NeuralNetwork &);

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
